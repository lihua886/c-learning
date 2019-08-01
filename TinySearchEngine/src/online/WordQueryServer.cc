#include "WordQueryServer.h"    
#include "Connection.h"
#include <iostream>
using std::cout;
using std::endl;

namespace wd{
//  构造函数 
WordQueryServer::WordQueryServer(const string & filename)
        :_conf(filename)
        ,_wordQuery(_conf)
        ,_tcpserver(_conf.getPort(),_conf.getIp())
        ,_threadpool(_conf.getThreadNum(),_conf.getQueueSize())
        {}
//  开始提供服务 
void WordQueryServer::start(){
     //LogInfo("process begin running\n");
 //    _conf.print();
     cout<<"port= "<<_conf.getPort()<<" ip= "<<_conf.getIp()<<endl;
     cout<<"threadnum= "<<_conf.getThreadNum()<<"qsize= "<<_conf.getQueueSize()<<endl;
     _wordQuery.loadLibrary();
     _threadpool.start();
     _tcpserver.setConnectionCallback(std::bind(&WordQueryServer::onConnection,this,std::placeholders::_1));
     _tcpserver.setMassageCallback(std::bind(&WordQueryServer::onMessage,this,std::placeholders::_1));
     _tcpserver.setCloseCallback(std::bind(&WordQueryServer::onClose,this,std::placeholders::_1));
     _tcpserver.start();
    
}
//   被注册回调函数，提供给TcpServer使用 
void WordQueryServer::onConnection(const TcpConnectionPtr & conn){
    std::cout << conn->toString() << " has connected!" << std::endl;
} 
//  被注册回调函数，提供给TcpServer使用 
void WordQueryServer::onMessage(const TcpConnectionPtr & conn){
    std::string msg = conn->receive();
    std::cout << ">> receive msg from client: " << msg << std::endl;
    
    _threadpool.addTask(std::bind(&WordQueryServer::doTaskThread,this,conn,msg));
} 
// 被注册回调函数，提供给TcpServer使用 
void WordQueryServer::onClose(const TcpConnectionPtr & conn){
    std::cout << ">> " << conn->toString() << " has closed!" << std::endl;
}

//   该方法由线程池的某一个线程执行 
void WordQueryServer::doTaskThread(const TcpConnectionPtr & conn, const string & msg){
    string response=_wordQuery.doQuery(msg);
    cout<<"response to IO thread"<<endl;
    int sz=response.size();
    string message(std::to_string(sz));
    cout<<"massage size= "<<message<<endl;
    message.append("\n").append(response);
    conn->sendInLoop(message);
}





}//end of wd
