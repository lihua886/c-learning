#pragma once
#include "Nocopyable.h"
#include <pthread.h>

namespace wd{
class MutexLock
:Nocopyable
{
public:
    MutexLock(); 
    ~MutexLock(); 
    void lock();
    void unlock();
    pthread_mutex_t * getMutexLockPtr() { return &_mutex; }
private:
    pthread_mutex_t _mutex;
    bool _isLocking;
};


class MutexGuard{
public:
    MutexGuard(MutexLock&  mutex)
    :_mutex(mutex){
        _mutex.lock();
    }
    ~MutexGuard(){
        _mutex.unlock();
    }
private:
    MutexLock & _mutex;
};




}// end of wd
