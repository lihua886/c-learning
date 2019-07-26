#pragma once

#include <string>
#include <map>
#include <cstdlib>
using std::map;
using std::string;


namespace wd{
class Myconf
{
public:
    static Myconf * getInstance(){
        if(_pInstance==nullptr){
            _pInstance=new Myconf();
            atexit(destroy);
        }
        return _pInstance;
    }
    static void destroy(){
        if(_pInstance){
            delete _pInstance;
            _pInstance=nullptr;
        }
    }
    map<string,string> & getConfigMap(){
        return _configmap;
    }
    string getip();
    int getport();
    size_t getthreadnum();
    size_t getqsize();
    string getdictpath();
    string getindexpath();
    string getcachepath();
    void show_conf();
private:
    Myconf(){
        readConf();
    } 
    ~Myconf(){}
    void readConf();
private:
    string _path;
    map<string,string> _configmap;
    static Myconf* _pInstance;
};


}

