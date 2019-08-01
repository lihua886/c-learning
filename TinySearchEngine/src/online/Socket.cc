#include "Socket.h"
#include <func.h>


Socket::Socket(){
    _fd=socket(AF_INET,SOCK_STREAM,0);
    if(_fd==-1){
        perror("socket");
    }
}
Socket::Socket(int fd)
    :_fd(fd){}

int Socket::fd(){
    return _fd;
}
void Socket::shutdown(){
     ::shutdown(_fd,SHUT_WR);        
}
Socket::~Socket(){
    ::close(_fd);
}
