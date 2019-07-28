#include "CacheManger.h"
#include "Myconf.h"
#include <iostream>
#include <functional>


#define __TRACE(...) fprintf(stdout, "file[%s]line[%u]func[%s]::",__FILE__,__LINE__,__func__);\
    fprintf(stdout,__VA_ARGS__)
namespace wd{



    
vector<Cache> CacheManger::_cachelist(Myconf::getInstance()->getthreadnum());    

MutexLock CacheManger::_mutex;

void CacheManger::init(){
    for(size_t i=0;i<Myconf::getInstance()->getthreadnum();++i){
         _cachelist[i].readFromFile(Myconf::getInstance()->getcachepath());
    }
#if 0
    for(auto &it:_cachelist){
        it.print();
    }
#endif
}

void CacheManger::periodUpdate(){
#if 1
    __TRACE("catch update begin\n");
    _cachelist[0].print();
#endif
    for(size_t i=1;i<Myconf::getInstance()->getthreadnum();++i){
        {
            _cachelist[i].update(_cachelist[0]);
        }
    }
    _cachelist[0].writeToFile(Myconf::getInstance()->getcachepath());
}
    
void CacheManger::periodUpdate1(const string & key){
    
    {
        MutexGuard mutex(_mutex);
        _cachelist[0].getElement(key);
    }

}
void CacheManger::periodUpdate2(const std::string &key, const std::string & value){
    {
        MutexGuard mutex(_mutex);
        _cachelist[0].addElement(key,value);
    }

}


}//end of wd
