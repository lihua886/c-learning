#pragma once

#include <pthread.h>
#include <functional>
namespace wd{

namespace  current_thread{
    extern __thread size_t threadnum;
}

class Thread
{
    using threadCallback=std::function<void()>;
public:
    Thread(threadCallback&& cb,size_t index) ;
    void start();
    void join();
    ~Thread();
private:
    static void* threadfunc(void *arg);
private:
    pthread_t _id;
    threadCallback _cb;
    bool _isRuning;
    size_t _index;
};


}// end of wd

