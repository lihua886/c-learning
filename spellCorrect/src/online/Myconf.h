#pragma once

#include <string>
#include <map>
using std::map;
using std::string;


namespace wd{
class Myconf
{
public:
    Myconf(const string&  path) 
        :_path(path){
            readConf();
        }
    map<string,string> & getConfigMap(){
        return _configmap;
    }
    void show_conf();
private:
    void readConf();
private:
    string _path;
    map<string,string> _configmap;
};


}

