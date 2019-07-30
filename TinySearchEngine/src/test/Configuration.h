#pragma once

#include <string>
#include <map>
#include <set>
using std::string;
using std::map;
using std::set;


namespace  wd{

class Configuration
{
public:
    Configuration(const string & ConfigFilePath)
    :_filepath(ConfigFilePath){}
    ~Configuration() {}

    void readConfigFile();
    void readStopWords();

    void print() const; 
    set<string> & getStopWords() { return _stopwords; }
    map<string,string> & getConfigMMap()  { return _configMap; }
private:
    string _filepath;
    map<string,string> _configMap;
    set<string>  _stopwords;
};



}// end of wd
