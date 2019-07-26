#include "TaskQueue.h"
#include <iostream>


namespace wd{

TaskQueue::TaskQueue(size_t qSize)
    :_mutex()
    ,_notempty(_mutex)
    ,_notfull(_mutex)
    ,_qSize(qSize)
    , _flag(true){}
    
void TaskQueue::push(Task &task){
    {
        MutexGuard mutex(_mutex);
        while(full()){
            _notfull.wait();
        }
        _tasks.push(task);
    }
        _notempty.notify();
}
Task TaskQueue::pop(){
     Task task;
     MutexGuard mutex(_mutex);
     while(empty()&&_flag){
         _notempty.wait();
     }
     if(_flag){
         task=_tasks.front();
         _tasks.pop();
         _notfull.notify();
         return task;
     }else{
         return nullptr;
     }
    
}
bool TaskQueue::empty(){
    return _tasks.empty();
}
bool TaskQueue::full(){
    return _tasks.size()==_qSize;
}
void TaskQueue::wakeup(){
    _flag=false;
    _notempty.notifyAll();
}


}// end of wd
