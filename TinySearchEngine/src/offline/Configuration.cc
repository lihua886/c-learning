#include "Configuration.h"    
#include <fstream>
#include <sstream>
#include <iostream>
using std::cout;
using std::endl;
using std::istringstream;
using std::ifstream;


namespace  wd{





void Configuration::readConfigFile(){
    ifstream ifs(_filepath);
    string line;
    string word,key;
    while(std::getline(ifs,line)){
        std::istringstream iss(line);
        iss>>word>>key;
        _configMap[word]=key;
    }
}

void Configuration::print() const{
    for(auto &it:_configMap){
        cout<<it.first<<"-->"<<it.second<<endl;
    }
    for(auto &it:_stopwords){
        cout<<it<<endl;
    }
}

void Configuration::readStopWords(){
    ifstream ifs(_configMap["stopwords"].c_str());
    string line;
    while(std::getline(ifs,line)){
        _stopwords.insert(line);
    }
}









}//end of wd
