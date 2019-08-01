#include "InetAddress.h"
#include <string.h>
namespace wd{
InetAddress::InetAddress(unsigned port){
    memset(&_addr,0,sizeof(struct sockaddr_in));
    _addr.sin_family=AF_INET;
    _addr.sin_port=htons(port);
    _addr.sin_addr.s_addr=INADDR_ANY;
}
InetAddress::InetAddress(const std::string & ip,unsigned port){
    memset(&_addr,0,sizeof(struct sockaddr_in));
    _addr.sin_family=AF_INET;
    _addr.sin_port=htons(port);
    _addr.sin_addr.s_addr=inet_addr(ip.c_str());
}
InetAddress::InetAddress(const struct sockaddr_in &addr)
    :_addr(addr){}

std::string InetAddress::ip() const{
    return std::string(::inet_ntoa(_addr.sin_addr));
}
unsigned short InetAddress::port() const{
     return ::ntohs(_addr.sin_port);
}






}//end of wd
