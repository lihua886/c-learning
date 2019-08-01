#pragma once

#include "Nocopyable.h"
#include <pthread.h>


namespace  wd{
class MutexLock;
class Condition
:Nocopyable
{
public:
    Condition(MutexLock & mutex); 
    void wait();
    void notify();
    void notifyAll();
    ~Condition(); 
private:
    pthread_cond_t  _cond;    
    MutexLock & _mutex;     
};


}// end of wd
