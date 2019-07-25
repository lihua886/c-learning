#include "Acceptor.h"
#include <sys/types.h>
#include <sys/socket.h>
namespace  wd{
Acceptor::Acceptor(unsigned int port,const std::string & ip)
:_addr(ip,port)
,listenSocket(){}
Acceptor::Acceptor(unsigned int port)
:_addr(port)
,listenSocket(){}
void Acceptor::bind(){
    int ret=::bind(listenSocket.fd(),(struct sockaddr*)_addr.getInetaddressPtr(),sizeof(struct sockaddr));
    if(ret==-1){
        perror("bind");
    }
}
void Acceptor::listen(){
    int ret=::listen(listenSocket.fd(),10);
    if(ret==-1){
        perror("listen");
    }
}
int Acceptor::accept(){
    int fd=::accept(listenSocket.fd(),nullptr,0);
    if(fd==-1){
        perror("accept");
    }
    return fd;
}
    
void Acceptor::ready(){
    setReuseAddr(true);
    setReusePort(true);
    bind();
    listen();
}
void Acceptor::setReuseAddr(bool on){
    int one=on;
    if(setsockopt(listenSocket.fd()
                  ,SOL_SOCKET
                  ,SO_REUSEADDR
                  ,&one
                  ,sizeof(one))<0){
        perror("setsockopt");
    }
}
void Acceptor::setReusePort(bool on){
    int one =on;
    if(setsockopt(listenSocket.fd()
                  ,SOL_SOCKET
                  ,SO_REUSEPORT
                  ,&one
                  ,sizeof(one))<0){
        perror("setsockopt");
    }
}

int Acceptor::fd(){
    return listenSocket.fd(); 
}
 



}

