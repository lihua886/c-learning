#pragma once

#include "Socket.h"
#include "InetAddress.h"
#include "SocketIO.h"
#include <memory>
#include <functional>


namespace wd{
struct train{
    int datalen;
    char data[4096];
};
class Eventloop;
class Connection
:public std::enable_shared_from_this<Connection>
{
    using ConnectionPtr=std::shared_ptr<Connection>;
    using ConnectionCallback=std::function<void(ConnectionPtr)>;
public:
    Connection(int fd,Eventloop *);
    ~Connection();
    
    
    std::string receive();
    void send(const std::string & msg);
    void sendInLoop(const std::string &msg);

    std::string toString();  //打印连接
    void shutdown();  // 
    void setConnectionCallback(const ConnectionCallback & cb){
        _onconnection=std::move(cb);
    }
    void setMassageCallback(const ConnectionCallback & cb){
        _onmessage=std::move(cb);
    }
    void setCloseCallback(const ConnectionCallback & cb){
        _onclose=std::move(cb);
    }
    void handleConnectionCallback();
    void handleMassageCallback();
    void handleCloseCallback();
private:
    InetAddress getlocaladdr();
    InetAddress getpeeraddr();
private:
    Socket _sock;
    SocketIO  _socketio;
    InetAddress _localaddr;
    InetAddress _peeraddr;
    bool _isShutDownWrite;
    Eventloop * _loop;

    ConnectionCallback _onconnection;
    ConnectionCallback _onmessage;
    ConnectionCallback _onclose;

    train _train;
};
}
