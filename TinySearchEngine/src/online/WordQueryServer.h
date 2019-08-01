#pragma once

#include "Configuration.h"
#include "Tcpserver.h"
#include "Threadpool.h"
#include "WordQuery.h"
#include <memory>
using std::shared_ptr;


namespace wd{
class Connection;
class WordQueryServer
{
    using TcpConnectionPtr=std::shared_ptr<Connection>;
public:

    WordQueryServer(const string & filename);  //  构造函数
    void start();  //  开始提供服务
    void onConnection(const TcpConnectionPtr & conn); //   被注册回调函数，提供给TcpServer使用
    void onMessage(const TcpConnectionPtr & conn); //  被注册回调函数，提供给TcpServer使用
    void onClose(const TcpConnectionPtr & conn); // 被注册回调函数，提供给TcpServer使用
    void doTaskThread(const TcpConnectionPtr & conn, const string & msg); //   该方法由线程池的某一个线程执行
private:
    Configuration _conf;// 配置类对象
    WordQuery _wordQuery; //  查询类对象
    Tcpserver _tcpserver;  // TCP通信对象
    Threadpool _threadpool; //  执行文本纠错结果的缓存线程类
};





}// end of wd
