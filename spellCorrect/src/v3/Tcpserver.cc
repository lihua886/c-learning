#include "Tcpserver.h"



namespace wd{
Tcpserver::Tcpserver(unsigned int port,const std::string & ip)
    :_acceptor(port,ip)
    ,_loop(_acceptor){}
     
void Tcpserver::start(){
    _acceptor.ready();
    _loop.loop();
}



void Tcpserver::setConnectionCallback(ConnectionCallback && cb){
    _loop.setConnectionCallback(std::move(cb));
}
void Tcpserver::setMassageCallback(ConnectionCallback && cb){
     _loop.setMassageCallback(std::move(cb));
}
void Tcpserver::setCloseCallback(ConnectionCallback && cb){
    _loop.setCloseCallback(std::move(cb));
}

}

