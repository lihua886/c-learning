#include "Connection.h"
#include "Eventloop.h"
#include "Mylogger.h"
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sstream>
#include <string>
using std::string;




namespace wd{



Connection::Connection(int fd,Eventloop * loop)
:_sock(fd)
,_socketio(fd)
,_localaddr(getlocaladdr())
,_peeraddr(getpeeraddr())
,_isShutDownWrite(false)
,_loop(loop){
    memset(&_train,0,sizeof(_train));
}


Connection::~Connection()
{
    if(!_isShutDownWrite){
        shutdown();
    }
}
std::string Connection::receive(){
    char buf[65535]={0};
    _socketio.readline(buf,sizeof(buf));
    return std::string(buf);
}
void Connection::send(const std::string & msg){
     _train.datalen=msg.size();
     strcpy(_train.data,msg.c_str());
     _socketio.writen(&_train,msg.size()+4);
}
std::string Connection::toString(){
    std::ostringstream oss;
    oss<<_localaddr.ip()<<":"<<_localaddr.port()
       <<"---->"<<_peeraddr.ip()<<":"<<_peeraddr.port()<<std::endl; 
    return oss.str();
}  //打印连接
void Connection::shutdown(){
    if(_isShutDownWrite){
        _isShutDownWrite=true;
        _sock.shutdown();
    }
}


void Connection::sendInLoop(const std::string &msg){
   LogInfo("return %d client %s\n",_sock.fd(),msg.c_str());
   _loop->runInLoop(std::bind(&Connection::send,this,msg)); 
}
InetAddress Connection::getlocaladdr(){
    struct sockaddr_in addr;
    socklen_t len=sizeof(struct sockaddr);
    if(::getsockname(_sock.fd(),(struct sockaddr*)&addr,&len)<0)
        perror("getsockname");
    return InetAddress(addr);
}
InetAddress Connection::getpeeraddr(){
    struct sockaddr_in addr;
    socklen_t len=sizeof(sockaddr);
    if(::getpeername(_sock.fd(),(struct sockaddr*)&addr,&len)<0)
        perror("getpeername");
    return InetAddress(addr);
}

void Connection::handleConnectionCallback(){
     if(_onconnection)
        _onconnection(shared_from_this());
}
void Connection::handleMassageCallback(){
    if(_onmessage)
        _onmessage(shared_from_this());
}
void Connection::handleCloseCallback(){
    if(_onclose)
        _onclose(shared_from_this());
}
    
    






}//end of wd
