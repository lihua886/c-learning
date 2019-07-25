#include "Myconf.h"
#include <fstream>
#include <sstream>
#include <func.h>
#include <iostream>
#include <cstdlib>
using std::ifstream;
using std::istringstream;
using std::cout;
using std::endl;


namespace  wd{
Myconf* Myconf::_pInstance=nullptr;

void Myconf::readConf(){
    ifstream ifs("/home/fsq/study/c++/c-learning/spellCorrect/conf/myconf");
    string line;
    string word1,word2;
    while(std::getline(ifs,line)){
        std::istringstream  iss(line);
        iss>>word1>>word2;
        _configmap[word1]=word2;
    }
}

string Myconf::getip(){
    return  _configmap[string("myip")]; 
}
int Myconf::getport(){
    return std::atoi(_configmap[string("myport")].c_str());
}
size_t Myconf::getthreadnum(){
    return std::atoi(_configmap[string("mythreadnum")].c_str());
}
size_t Myconf::getqsize(){
    return std::atoi(_configmap[string("myqsize")].c_str());
}
string Myconf::getdictpath(){
    return  _configmap[string("mydict")]; 
}
string Myconf::getindexpath(){
    return  _configmap[string("myindex")];
}


void show_conf();
void Myconf::show_conf(){
    for(auto &it:_configmap){
       cout<<it.first<<" "<<it.second<<endl;
    }
}



}
