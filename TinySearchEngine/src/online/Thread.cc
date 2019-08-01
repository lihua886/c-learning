#include "Thread.h"


namespace wd{

Thread::Thread(threadCallback && cb)
    :_id(0)
    ,_cb(std::move(cb))
    ,_isRuning(false){}
void Thread::start(){
    pthread_create(&_id,NULL,threadfunc,this);
    _isRuning=true;
}
void Thread::join(){
    if(_isRuning)
        pthread_join(_id,NULL);
}
void* Thread::threadfunc(void *arg){
      Thread * pthread=static_cast<Thread*>(arg);
      if(pthread){
          pthread->_cb();
      }
      return nullptr;
}
Thread::~Thread(){
    if(_isRuning){
        _isRuning=false;
    }
}



}// end of wd;

