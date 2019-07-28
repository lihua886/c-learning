#pragma once
#include "Cache.h"
#include "MutexLock.h"
#include <vector>
#include <stdlib.h>
#include <memory>
using std::vector;
using std::shared_ptr;

namespace  wd{


class CacheManger
{
public:
    static void init();
    static Cache & getCache(size_t index){return _cachelist[index];}
    static void periodUpdate();
    static void periodUpdate2(size_t );
private:
    static vector<Cache> _cachelist;    
    static MutexLock _mutex;
};





}//end of wd
