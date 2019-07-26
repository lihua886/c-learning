#include "Thread.h"


namespace wd{


namespace  current_thread{
   __thread size_t threadnum = 0;
}

struct ThreadData{
    using threadCallback=std::function<void()>;
    
    ThreadData(size_t index,threadCallback && cb)
        :_index(index)
        ,_cb(std::move(cb)){}

    size_t _index;
    threadCallback _cb;


    void runInThread(){
        current_thread::threadnum = _index;
        if(_cb){
            _cb();
        }
    }
};

Thread::Thread(threadCallback && cb,size_t index)
    :_id(0)
    ,_cb(std::move(cb))
    ,_isRuning(false)
    ,_index(index){}
void Thread::start(){
    ThreadData * threadData=new ThreadData(_index,std::move(_cb));
    pthread_create(&_id,NULL,threadfunc,threadData);
    _isRuning=true;
}
void Thread::join(){
    if(_isRuning)
        pthread_join(_id,NULL);
}
void* Thread::threadfunc(void *arg){
      ThreadData * threadData =static_cast<ThreadData*>(arg);
      if(threadData){
          threadData->runInThread();
      }
      delete threadData;
      return nullptr;
}
Thread::~Thread(){
    if(_isRuning){
        pthread_detach(_id);
    }
}



}// end of wd;

