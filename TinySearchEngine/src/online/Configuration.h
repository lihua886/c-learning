#pragma once

#include <string>
#include <map>
#include <set>
#include <stdlib.h>
using std::string;
using std::map;
using std::set;


namespace  wd{



class Configuration
{
public:
    Configuration(const string & ConfigFilePath)
        :_filepath(ConfigFilePath){
            readConfigFile();
            readStopWords();
        }
    ~Configuration() {}

    void readConfigFile();
    void readStopWords();
    string getIp(){ return _configMap["ip"]; }
    unsigned int getPort(){
        return ::atoi(_configMap["port"].c_str());
    }
    int getQueueSize(){ 
        return ::atoi(_configMap["queuesize"].c_str());
    }
    int getThreadNum(){
        return ::atoi(_configMap["threadnum"].c_str());
    }
    void print() const; 
    set<string> & getStopWords() { return _stopwords; }
    map<string,string> & getConfigMap()  { return _configMap; }
private:
    string _filepath;
    map<string,string> _configMap;
    set<string>  _stopwords;
};



}// end of wd
