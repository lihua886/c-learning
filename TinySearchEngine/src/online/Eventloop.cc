
#include "Eventloop.h"
#include "Acceptor.h"
#include "Connection.h"
#include <iostream>
#include <assert.h>
#include <sys/eventfd.h>
#include <unistd.h>
namespace wd{
Eventloop::Eventloop(Acceptor & accept)
    :_efd(createEpollFd())
    ,_eventFd(createEventFd())
    ,_accept(accept)
    ,_eventlist(1024)
    ,_islooping(false){
        addEpollFdRead(accept.fd());
        addEpollFdRead(_eventFd);
    }
void Eventloop::loop(){
    _islooping=true;
    while(_islooping){
        waitEpollFd();
    }
}
void Eventloop::unloop(){
    if(_islooping){
        _islooping=false;
    }
}
    
void Eventloop::runInLoop(Functor && cb){
    {
        MutexGuard autoMutex(_mutex);
        _pendingFunctors.push_back(std::move(cb));
    }
    wakeup();
}
void Eventloop::waitEpollFd(){
    int nReady;
    do{
        nReady=::epoll_wait(_efd,&*_eventlist.begin(),_eventlist.size(),5000);  
     }while(nReady==-1&&errno==EINTR);
    if(nReady==-1){
        perror("epoll_wait");
        return;
    }else if(nReady==0){  //返回0表示超时
        std::cout<<">> epoll timeout"<<std::endl;
    }else{
        if(nReady==(int)_eventlist.size()){
            _eventlist.resize(2 * nReady);
        }
        for(int i=0;i<nReady;++i){
            int fd=_eventlist[i].data.fd;
            if(fd==_accept.fd()){
                if(_eventlist[i].events& EPOLLIN){
                    handleNewConnection();
                }
            }else if(fd==_eventFd){
                if(_eventlist[i].events& EPOLLIN){
                    handleRead();
                    doPendingFunctors();// 发送给客户端数据
                }
            }else{
                if(_eventlist[i].events& EPOLLIN){
                    handleMessage(fd);
                }
            }
        }
    }
}
void Eventloop::handleNewConnection(){// 处理新连接 
    int peerfd=_accept.accept();
    addEpollFdRead(peerfd);
    ConnectionPtr conn(new Connection(peerfd,this));
    //注册连接，传递信息，关闭连接的回调函数
    conn->setConnectionCallback(_onconnection);
    conn->setMassageCallback(_onmessage);
    conn->setCloseCallback(_onclose);
    _conns.insert(std::make_pair(peerfd,conn));
    conn->handleConnectionCallback();// 执行新连接的回调函数
}
void Eventloop::handleMessage(int fd){// 处理消息 
   bool ret=isConnectionClosed(fd);// 
   auto iter=_conns.find(fd);
   assert(iter!=_conns.end());
   if(ret){
       delEpollFdRead(fd);
       iter->second->handleCloseCallback();
       _conns.erase(fd);
   }else{
       iter->second->handleMassageCallback();
   }
} 
int Eventloop::createEpollFd(){// 创建efd 
    int ret=epoll_create(1);
    if(ret==-1){
        perror("epoll_create");
    }
    return ret;
} 
int Eventloop::createEventFd(){
    int ret=eventfd(10,0);
    if(ret==-1){
        perror("eventfd");
    }
    return ret;
}
void Eventloop::wakeup(){
    uint64_t one=1;
    int ret=write(_eventFd,&one,sizeof(one));
    if(ret != sizeof(one)){
        perror("read");
    }

}


void Eventloop::handleRead(){
    uint64_t one;
    int ret=read(_eventFd,&one,sizeof(one));
    if(ret != sizeof(one)){
        perror("read");
    }
}

void Eventloop::doPendingFunctors(){
    std::vector<Functor> tmp;
    {
        MutexGuard autoLock(_mutex);
        tmp.swap(_pendingFunctors);
    }
    for(auto & functor:tmp){
        functor();
    }
}
void Eventloop::addEpollFdRead(int fd){
    struct epoll_event evs;
    evs.events=EPOLLIN;
    evs.data.fd=fd;
    int ret=epoll_ctl(_efd,EPOLL_CTL_ADD,fd,&evs);
    if(ret==-1){
        perror("epoll_ctl");
    }
}
void Eventloop::delEpollFdRead(int fd){
    struct epoll_event evs;
    evs.data.fd=fd;
    int ret=epoll_ctl(_efd,EPOLL_CTL_DEL,fd,&evs);
    if(ret==-1){
        perror("epoll_ctl");
    }
}
bool Eventloop::isConnectionClosed(int fd){  // recv返回0表示连接断开
    int ret;
    do{
        char buf[1000]={0};
        ret=recv(fd,buf,sizeof(buf),MSG_PEEK);
    }while(ret==-1&&errno==EINTR);
    
    
    return (ret==0);
}



}
