#include "Cache.h"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <json/json.h>
#include <json/reader.h>
using std::ifstream;
using std::ofstream;
using std::istringstream;
using std::ostringstream;
#define __TRACE(...) fprintf(stdout, "file[%s]line[%u]func[%s]::",__FILE__,__LINE__,__func__);\
    fprintf(stdout,__VA_ARGS__)


namespace  wd{

// 构造函数 
Cache::Cache(const Cache & cache){
    for(auto &it:cache._list){
        this->addElement(it._key,it._value);
    }
} 
//往缓存中添加数据
void Cache::addElement(const std::string &key, const std::string & value){
   auto it=_hashMap.find(key);
   if(it==_hashMap.end()){
       if(_list.size()==_capacity){// 如果满了就淘汰链表尾部的
           string deletekey=_list.back()._key;
           _list.pop_back();
           _hashMap.erase(deletekey);
       }
       _list.push_front(CacheNode(key,value));
       _hashMap[key]=_list.begin();
   }else{
     //  it->second->_value=value;
     //  _list.splice(_list.begin(),_list,it->second);
     //  _hashMap[key]=_list.begin();
   }
}
void Cache::print() const{
   __TRACE("_list.size=%ld,_hashMap.size=%ld\n",_list.size(),_hashMap.size());
   for(auto &it:_list){
       std::cout<<it._key;
       //std::cout<<"-->"<<it._value;
       std::cout<<std::endl;
   }
#if 0
   for(auto &it:_hashMap){
       std::cout<<it.first<<std::endl;
   }
#endif
}
string  Cache::getElement(const string & key){
//   __TRACE("%s\n",key.c_str());
   auto it=_hashMap.find(key);
   if(it==_hashMap.end()){
        return string();
   }else{
       string result=it->second->_value;
       _list.splice(_list.begin(),_list,it->second);
       _hashMap[key]=_list.begin();
       return result;
   }
}
// 从文件中读取缓存信息 
void Cache::readFromFile(const std::string & filename){
    ifstream ifs(filename);
    string value;
    std::getline(ifs,value);
    while(getline(ifs,value)){
        if(value.length()==1){
            continue;
        }
       // __TRACE("%s\n",value.c_str());
        std::istringstream iss(value);
        string key;
        iss>>key;
        key.erase(key.begin());
        key.erase(key.end()-1);
        std::ostringstream oss;
        oss<<"{"<<std::endl<<value<<std::endl<<"}"<<std::endl;
        CacheNode mycachenode(key,oss.str());
        _list.push_front(mycachenode);
        _hashMap[key]=_list.begin();
    }
#if 0
   __TRACE("_list.size=%ld,_hashMap.size=%ld\n",_list.size(),_hashMap.size());
   for(auto &it:_list){
       std::cout<<it._key<<"-->"<<it._value<<std::endl;
   }
#endif
}
// 将缓存信息写入到文件中  
void Cache::writeToFile(const std::string & filename){
    ofstream ofs(filename);
    ofs<<"{"<<std::endl;
    for(auto it=_list.crbegin();it!=_list.crend();++it){
        ofs<<it->_value<<","<<std::endl;
    }
    ofs<<"}";
}

//更新缓存信息 
void Cache::update(const Cache & rhs){
    _list.clear();
    _hashMap.clear();
    for(auto it=rhs._list.crbegin();it!=rhs._list.crend();++it){
        _list.push_front(CacheNode(*it));
        _hashMap[it->_key]=_list.begin();
    }
}
void Cache::cacheInsert(const Cache & rhs){
    for(auto &it:rhs._list){
        this->addElement(it._key,it._value);
    }
}






}//end of wd

