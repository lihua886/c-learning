#pragma once
#include <unordered_map>
#include <string>
#include <list>
using std::string;
using std::list;
using std::unordered_map;
namespace  wd{

class Cache
{
    struct CacheNode{
        CacheNode(const string &key,const string &value)
            :_key(key),_value(value){}
        //CacheNode(const CacheNode& rhs)
        //    :_key(rhs._key),_value(rhs._value){}
        string _key;
        string _value;
    };
public:
    Cache(){}
    //构造函数 
    Cache(const Cache & cache); // 构造函数
    //往缓存中添加数据
    void addElement(const std::string &key, const std::string & value);    
    // 从文件中读取缓存信息 
    void readFromFile(const std::string & filename); 
    // 将缓存信息写入到文件中  
    void writeToFile(const std::string & filename);  
    //更新缓存信息 
    void update(const Cache & rhs);
    //获取缓存信息
    string  getElement(const string & key);
    void cacheInsert(const Cache & rhs);
    size_t getSize(){ return _list.size(); }
private:
    size_t _capacity=10000;
    std::list<CacheNode> _list;
    // 采用hashTable进行缓存 
    std::unordered_map<string,list<CacheNode>::iterator> _hashMap; 
};


}//end of wd
