#include "SpellCorrectSever.h"
#include "Connection.h"
#include "Myconf.h"
#include "Task.h"
#include <cstdlib>
#include <iostream>
using std::cout;
using std::endl;

namespace wd{
SpellCorrectSever::SpellCorrectSever()
    :_tcpserver(Myconf::getInstance()->getport()
                ,Myconf::getInstance()->getip())
    ,_threadpool(Myconf::getInstance()->getthreadnum()
                ,Myconf::getInstance()->getqsize()){}

void SpellCorrectSever::stop(){
    _threadpool.stop();
}
void SpellCorrectSever::onConnection(const ConnectionPtr& conn ){
    std::cout << conn->toString() << " has connected!" << std::endl;
            conn->send("welcome to server.");
}
void SpellCorrectSever::onMessage(const ConnectionPtr& conn ){
    std::string msg = conn->receive();
    std::cout << ">> receive msg from client: " << msg << std::endl;
    
    
    
    __TRACE("addtask to sub thread\n");
    Mytask task(msg,conn);
    _threadpool.addTask(std::bind(&Mytask::process,task));
    __TRACE("addtask success \n");
}
void SpellCorrectSever::onClose(const ConnectionPtr& conn){
    std::cout << ">> " << conn->toString() << " has closed!" << std::endl;
}
void SpellCorrectSever::start(){
     _threadpool.start();
     _tcpserver.setConnectionCallback(std::bind(&SpellCorrectSever::onConnection,this,std::placeholders::_1));
     _tcpserver.setMassageCallback(std::bind(&SpellCorrectSever::onMessage,this,std::placeholders::_1));
     _tcpserver.setCloseCallback(std::bind(&SpellCorrectSever::onClose,this,std::placeholders::_1));
     _tcpserver.start();
}

}// end of wd
