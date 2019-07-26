#pragma once
#include "MutexLock.h"
#include <sys/epoll.h>
#include <vector>
#include <map>
#include <memory>
#include <functional>

namespace  wd{
class Connection;
class Acceptor;

class Eventloop
{
    using ConnectionPtr=std::shared_ptr<Connection>;
    using ConnectionCallback=std::function<void(ConnectionPtr)>;
    using Functor=std::function<void()>;
public:
    Eventloop(Acceptor & accpet);
    void loop();
    void unloop();
    void runInLoop(Functor && cb);
    void setConnectionCallback(ConnectionCallback && cb){
        _onconnection=std::move(cb);
    }
    void setMassageCallback(ConnectionCallback && cb){
        _onmessage=std::move(cb);
    }
    void setCloseCallback(ConnectionCallback && cb){
        _onclose=std::move(cb);
    }
private:
    void waitEpollFd();
    void handleNewConnection();// 处理新连接
    void handleMessage(int fd); // 处理消息
    
    
    int createEpollFd(); // 创建efd
    int createEventFd();// 创建eventfd 
    int createTimerfd();
    //eventfd处理
    void eventhandleRead();
    void wakeup();
    void doPendingFunctors();
   
    
    void timehandleRead();
    void updateCache();




    void addEpollFdRead(int fd); 
    void delEpollFdRead(int fd);
    bool isConnectionClosed(int fd);
    void setTimerfd(int initialTime=0, int intervalTime=6);
private:
    int _efd;
    int _eventFd;
    int _timerFd;
    Acceptor & _accept;
    std::vector<struct epoll_event> _eventlist;
    std::map<int ,ConnectionPtr> _conns;
    bool _islooping;

    MutexLock _mutex;
    std::vector<Functor> _pendingFunctors;

    ConnectionCallback _onconnection;
    ConnectionCallback _onmessage;
    ConnectionCallback _onclose;
};



}

