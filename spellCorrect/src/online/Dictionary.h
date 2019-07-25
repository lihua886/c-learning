#pragma once

#include <unordered_map>
#include <set>
#include <vector>
#include <string>
#include <cstdlib>
using std::pair;
using std::unordered_map;
using std::set;
using std::vector;
using std::string;

namespace  wd{
class Dictionary
{
public:
    static Dictionary * getInstance(){
        if(_pInstance==nullptr){
            _pInstance=new Dictionary;
            atexit(destroy);
        }
        return _pInstance;
    }
    static void destroy(){
        if(_pInstance){
            delete  _pInstance;
            _pInstance=nullptr;
        }
    }
    void readDictFile(const string & file);
    void readIndexFile(const string & file);
    void show_dict();
    void show_index();
    vector<pair<string, int>> & getDict(){
        return _dict;
    }
    unordered_map<string, set<int>> & getIndex(){
        return _indexTable;
    }
private:
    Dictionary(){}
    ~Dictionary() {}
private:
    vector<pair<string, int>> _dict;
    unordered_map<string, set<int>> _indexTable;
    static Dictionary * _pInstance;
};

}
