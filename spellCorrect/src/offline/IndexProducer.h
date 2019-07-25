#pragma once

#include "DictProducer.h"
#include <unordered_map>
#include <set>
#include <string>
#include <memory>
using std::shared_ptr;
using std::string;
using std::unordered_map;
using std::set;

namespace  wd{
class IndexProducer
{
public:
    IndexProducer(DictProducer * Dict){
        func(Dict);
    }
    void build_index();
    void build_cnindex();
    void store_index(const char * path);
private:
    void func(DictProducer * Dict){
        _dict= std::shared_ptr<map<string,int>>(new map<string,int>(Dict->_dict)); 
    }
private:
    std::unordered_map<string,set<int> > _index;
    shared_ptr<map<string,int>>  _dict;
};



}//end of wd
