#pragma once

#include "TaskQueue.h"
#include "Thread.h"
#include <vector>
#include <memory>

namespace wd{
using Threadptr=std::unique_ptr<Thread>;
class Threadpool
{
public:
    Threadpool(size_t,size_t );
    void start();
    void stop();
    void addTask(Task&& task);
private:
    Task getTask();
    void threadfunc();
private:
    size_t _threadNum;
    size_t _qSize;
    std::vector<Threadptr> _threads;
    TaskQueue _taskqueue;
    bool _isExit;
};



}// end of wd;
