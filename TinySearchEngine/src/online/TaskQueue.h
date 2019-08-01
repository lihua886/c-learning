#pragma once

#include "MutexLock.h"
#include "Condition.h"
#include <functional>
#include <queue>


namespace  wd{
using Task=std::function<void()>;
class TaskQueue
{
public:
    TaskQueue(size_t qSize=10);
    void push(Task & task);
    Task pop();
    bool empty();
    bool full();
    void wakeup();
private:
    MutexLock  _mutex;
    Condition  _notempty;
    Condition  _notfull;
    size_t _qSize;
    std::queue<Task> _tasks;
    bool _flag;
};


}
