#include "CacheManger.h"
#include "Myconf.h"
#include <iostream>
#include <functional>

#define __TRACE(...) fprintf(stdout, "file[%s]line[%u]func[%s]::",__FILE__,__LINE__,__func__);\
    fprintf(stdout,__VA_ARGS__)
namespace wd{

//CacheManger* CacheManger::_pInstance=nullptr;


    
vector<Cache> CacheManger::_cachelist(Myconf::getInstance()->getthreadnum());    

#if 1
void CacheManger::init(){
    for(size_t i=0;i<Myconf::getInstance()->getthreadnum();++i){
         _cachelist[i].readFromFile(Myconf::getInstance()->getcachepath());
        // __TRACE("cache.size=%ld,_cachelist.size()=%ld\n",_cachelist[i].getSize(),_cachelist.size());
    }
}
void CacheManger::periodUpdate(){
    for(size_t i=1;i<Myconf::getInstance()->getthreadnum();++i){
        _cachelist[0].cacheInsert(_cachelist[i]);
    //    __TRACE("_cache[0].size=%ld\n",_cachelist[0].getSize());
    //    __TRACE("_cache[0].size=%ld\n",_cachelist[i].getSize());
    }
    for(size_t i=1;i<Myconf::getInstance()->getthreadnum();++i){
        _cachelist[i].update(_cachelist[0]);
    }
    _cachelist[0].writeToFile(Myconf::getInstance()->getcachepath());
}


#endif





}//end of wd
