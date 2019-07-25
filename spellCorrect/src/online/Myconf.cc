#include "Myconf.h"
#include <fstream>
#include <sstream>
#include <func.h>
#include <iostream>
using std::ifstream;
using std::istringstream;
using std::cout;
using std::endl;


namespace  wd{

void Myconf::readConf(){
    ifstream ifs(_path);
    string line;
    string word1,word2;
    while(std::getline(ifs,line)){
        std::istringstream  iss(line);
        iss>>word1>>word2;
        _configmap[word1]=word2;
    }
}
void Myconf::show_conf(){
    for(auto &it:_configmap){
       cout<<it.first<<" "<<it.second<<endl;
    }
}



}
