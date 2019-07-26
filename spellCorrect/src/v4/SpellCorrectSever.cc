#include "SpellCorrectSever.h"
#include "Connection.h"
#include "Myconf.h"
#include "Task.h"
#include <cstdlib>
#include <iostream>
using std::cout;
using std::endl;
#define __TRACE(...) fprintf(stdout, "file[%s]line[%u]func[%s]::",__FILE__,__LINE__,__func__);\
    fprintf(stdout,__VA_ARGS__)

namespace wd{
SpellCorrectSever::SpellCorrectSever()
    :_tcpserver(Myconf::getInstance()->getport()
                ,Myconf::getInstance()->getip())
    ,_threadpool(Myconf::getInstance()->getthreadnum()
                ,Myconf::getInstance()->getqsize())
    {}

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
    
    
    
    Mytask task(msg,conn);
//    __TRACE("add task begin\n");
    _threadpool.addTask(std::bind(&Mytask::process,task));
//    __TRACE("add task success\n");
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
