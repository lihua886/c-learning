#pragma once

#include <unordered_map>
#include <set>
#include <string>
#include <memory>
#include <map>
using std::shared_ptr;
using std::string;
using std::unordered_map;
using std::set;
using std::map;

namespace  wd{
class IndexProducer
{
public:
    IndexProducer(){
        readDict();
    }
    void build_index();
    void build_cnindex();
    void store_index(const char * path);
private:
    void readDict();
private:
    std::unordered_map<string,set<int> > _index;
    map<string,int>  _dict;
};



}//end of wd
