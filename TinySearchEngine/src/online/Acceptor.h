#pragma once

#include "InetAddress.h"
#include "Socket.h"
#include <string>

namespace  wd{
class Acceptor
{
public:
    Acceptor(unsigned int port);
    Acceptor(unsigned int port,const std::string & ip);
    ~Acceptor() {}
    int accept();
    int fd();
    void ready();
private:
    void setReuseAddr(bool on);
    void setReusePort(bool on);
    void bind();
    void listen();

private:
    InetAddress _addr;
    Socket listenSocket;
};




}

