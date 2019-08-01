#pragma once

#include <pthread.h>
#include <functional>

namespace wd{
class Thread
{
    using threadCallback=std::function<void()>;
public:
    Thread(threadCallback&& cb) ;
    void start();
    void join();
    ~Thread();
private:
    static void* threadfunc(void *arg);
private:
    pthread_t _id;
    threadCallback _cb;
    bool _isRuning;
};


}// end of wd

