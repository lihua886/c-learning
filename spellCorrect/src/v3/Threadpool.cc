#include "Threadpool.h"
#include <stdlib.h>
#include <unistd.h>

namespace wd{
Threadpool::Threadpool(size_t threadnum,size_t sz)
:_threadNum(threadnum)
,_qSize(sz)
,_taskqueue(sz)
,_isExit(false){
        _threads.reserve(_threadNum);
}
void Threadpool::start(){
    for(size_t i=0;i<_threadNum;++i){
        Threadptr thread(new Thread(std::bind(&Threadpool::threadfunc,this)));
        _threads.emplace_back(std::move(thread));
    }
    for(auto & thread:_threads){
        thread->start();
    }
}
void Threadpool::stop(){
    if(!_isExit){
        //执行完任务
        
        while(!_taskqueue.empty()){::sleep(1);}
        _isExit=true;
        _taskqueue.wakeup();
        for(auto & thread:_threads){
            thread->join();
        }
    }
}

void Threadpool::addTask(Task&& task){
     _taskqueue.push(task);
}
Task Threadpool::getTask(){
    return _taskqueue.pop();
}
void Threadpool::threadfunc(){
    while(!_isExit){
        Task task=getTask();
        if(task){
            task();
        }
    }
}
}// end of wd
