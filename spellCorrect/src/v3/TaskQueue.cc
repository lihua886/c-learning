#include "TaskQueue.h"
#include <iostream>

#define __TRACE(...) fprintf(stdout, "file[%s]line[%u]func[%s]::",__FILE__,__LINE__,__func__);\
    fprintf(stdout,__VA_ARGS__)

namespace wd{

TaskQueue::TaskQueue(size_t qSize)
    :_mutex()
    ,_notempty(_mutex)
    ,_notfull(_mutex)
    ,_qSize(qSize)
    , _flag(true){}
    
void TaskQueue::push(Task &task){
    __TRACE("push task begin\n");
    {
        MutexGuard mutex(_mutex);
        while(full()){
            _notfull.wait();
        }
        _tasks.push(task);
    __TRACE("push task success\n");
    }
        _notempty.notify();
    __TRACE("push task success\n");
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
