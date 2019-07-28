#pragma once
#include "Cache.h"
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
private:
    static vector<Cache> _cachelist;    
};





}//end of wd
