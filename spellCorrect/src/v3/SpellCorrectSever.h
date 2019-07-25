#pragma once
#include "Tcpserver.h"
#include "Threadpool.h"

#define __TRACE(...) fprintf(stdout, "file[%s]line[%u]func[%s]::",__FILE__,__LINE__,__func__);\
    fprintf(stdout,__VA_ARGS__)
namespace  wd{
    using ConnectionPtr=std::shared_ptr<Connection>;
    
class SpellCorrectSever
{
public:
    SpellCorrectSever();
    void onConnection(const ConnectionPtr& );
    void onMessage(const ConnectionPtr& );
    void onClose(const ConnectionPtr& );
    
    
    void start();
    void stop();
    
private:
    Tcpserver _tcpserver;
    Threadpool _threadpool;
};



}//end of wd

