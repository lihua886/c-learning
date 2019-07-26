#pragma once

#include <arpa/inet.h>
#include <string>



namespace  wd{
class InetAddress
{
public:
    explicit
    InetAddress(unsigned port);
    InetAddress(const std::string & ip,unsigned port);
    InetAddress(const struct sockaddr_in &addr);

    std::string ip() const;
    unsigned short port() const;
    struct sockaddr_in * getInetaddressPtr() { return &_addr; }
    ~InetAddress() {}

private:
    struct sockaddr_in _addr;
};





}//end of namespace

