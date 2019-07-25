#pragma once
#include "Cache.h"
#include <vector>
#include <stdlib.h>
using std::vector;


namespace  wd{



class CacheManger
{
public:
    static CacheManger* getInstance(){
        if(_pInstance==nullptr){
            _pInstance=new CacheManger;
            atexit(destroy);
        }
        return _pInstance;
    }
    static void destroy(){
        if(_pInstance){
            delete _pInstance;
            _pInstance=nullptr;
        }
    }
    void init();
    Cache & getCache(size_t index){return _cachelist[index];}
    void periodUpdate();
private:
    CacheManger(); 
    ~CacheManger() {}
private:
    vector<Cache> _cachelist;    
    static CacheManger* _pInstance;
};





}//end of wd
