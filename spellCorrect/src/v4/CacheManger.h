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
   // static CacheManger* getInstance(){
   //     if(_pInstance==nullptr){
   //         _pInstance=new CacheManger;
   //         atexit(destroy);
   //     }
   //     return _pInstance;
   // }
   // static void destroy(){
   //     if(_pInstance){
   //         delete _pInstance;
   //         _pInstance=nullptr;
   //     }
   // }
    static void init();
    static Cache & getCache(size_t index){return _cachelist[index];}
   static void periodUpdate();
private:
    static vector<Cache> _cachelist;    
   // static CacheManger* _pInstance;
};





}//end of wd
