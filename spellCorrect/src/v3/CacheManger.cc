#include "CacheManger.h"
#include "Myconf.h"

#define __TRACE(...) fprintf(stdout, "file[%s]line[%u]func[%s]::",__FILE__,__LINE__,__func__);\
    fprintf(stdout,__VA_ARGS__)

namespace wd{

CacheManger* CacheManger::_pInstance=nullptr;

CacheManger::CacheManger(){
    int size=Myconf::getInstance()->getthreadnum();
    _cachelist.reserve(size);
    __TRACE("%ld\n",_cachelist.size());
}

void CacheManger::init(){
    for(size_t i=0;i<_cachelist.size();++i){
         Cache cache;
         cache.readFromFile(Myconf::getInstance()->getcachepath());
         _cachelist.push_back(std::move(cache));
    }
    __TRACE("%ld\n",_cachelist.size());

}
void CacheManger::periodUpdate(){
    for(size_t i=1;i<_cachelist.size();++i){
        _cachelist[0].cacheInsert(_cachelist[i]);
    }
    for(size_t i=1;i<_cachelist.size();++i){
        _cachelist[i].update(_cachelist[0]);
    }
    _cachelist[0].writeToFile(Myconf::getInstance()->getcachepath());
}








}//end of wd
