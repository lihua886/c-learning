#include "Cache.h"
#include <algorithm>
#include <fstream>
#include <json/json.h>
#include <json/reader.h>
using std::ifstream;
using std::ofstream;


namespace  wd{



Cache::Cache(size_t capacity)
    :_capacity(capacity){}
// 构造函数 
#if 1
Cache::Cache(const Cache & cache){
    std::list<CacheNode> _tmplist(std::move(cache._list));
    std::unordered_map<string,list<CacheNode>::iterator> _tmphashMap(std::move(cache._hashMap));
    _list.swap(_tmplist);
    _hashMap.swap(_tmphashMap);
} 
#endif
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
       it->second->_value=value;
       _list.splice(_list.begin(),_list,it->second);
       _hashMap[key]=_list.begin();
   }
}
string  Cache::getElement(const string & key){
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
        value.erase(value.end()-1);
        if(value.size()==0){
            break;
        }
        Json::Reader reader;
        Json::Value myjson;
        if(!reader.parse(value,myjson)){
            return;
        }
        string key=myjson.getMemberNames().front();
        CacheNode mycachenode(key,value);
        _list.push_front(mycachenode);
        _hashMap[key]=_list.begin();
    }
}
    // 将缓存信息写入到文件中  
void Cache::writeToFile(const std::string & filename){
    ofstream ofs(filename);
    ofs<<"{"<<std::endl;
    for(auto & it:_list){
        ofs<<it._value<<","<<std::endl;
    }
    ofs<<"}";
}

#if 1
//更新缓存信息 
void Cache::update(const Cache & rhs){
//    _list.clear();
//    _hashMap.clear();
//    cacheInsert(rhs);
}
void Cache::cacheInsert(const Cache & rhs){

}

#endif








}//end of wd

