#pragma once

#include "Acceptor.h"
#include "Eventloop.h"
#include <string>
#include <memory>
#include <functional>

namespace wd{
class Acceptor;
class Eventloop;
class Connection;
class Tcpserver
{
public:
    using ConnectionPtr=std::shared_ptr<Connection>;
    using ConnectionCallback=std::function<void(ConnectionPtr)>;
    Tcpserver(unsigned int port,const std::string & ip);
    void start();
    void setConnectionCallback(ConnectionCallback && cb);
    void setMassageCallback(ConnectionCallback && cb);
    void setCloseCallback(ConnectionCallback && cb);
private:
    Acceptor  _acceptor;
    Eventloop  _loop;   
};


}// end of wd
