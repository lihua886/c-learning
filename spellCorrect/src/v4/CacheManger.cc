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
         Cache* cache(new Cache);
         cache->readFromFile(Myconf::getInstance()->getcachepath());
         _cachelist.push_back(std::move(*cache));
    }
}
void CacheManger::periodUpdate(){
//    std::cout<<"cache task begin"<<std::endl;
    for(size_t i=1;i<Myconf::getInstance()->getthreadnum();++i){
        _cachelist[0].cacheInsert(_cachelist[i]);
    }
    for(size_t i=1;i<Myconf::getInstance()->getthreadnum();++i){
        _cachelist[i].update(_cachelist[0]);
    }
    _cachelist[0].writeToFile(Myconf::getInstance()->getcachepath());
}


#endif





}//end of wd
