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
        Threadptr thread(new Thread(std::bind(&Threadpool::threadfunc,this),i));
        _threads.emplace_back(std::move(thread));
    }
    for(auto & thread:_threads){
        thread->start();
    }
}
void Threadpool::stop(){
    if(!_isExit){
        //执行完任务
        //以防任务没有执行完毕
        while(!_taskqueue.empty()){::sleep(1);}
       
        _isExit=true;
        _taskqueue.wakeup();//以防在_isExit修改之前，线程走到了wait
        
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
//线程执行的任务
void Threadpool::threadfunc(){
    while(!_isExit){
        Task task=getTask();
        if(task){
            task();
        }
    }
}
}// end of wd
