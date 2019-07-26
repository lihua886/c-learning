#pragma once

#include <vector>
#include <string>
#include "../../include/cppjieba/Jieba.hpp"

using std::string;
using std::vector;


namespace  wd{
const char* const DICT_PATH = "/home/fsq/cppjieba/dict/jieba.dict.utf8";
const char* const HMM_PATH = "/home/fsq/cppjieba/dict/hmm_model.utf8";
const char* const USER_DICT_PATH = "/home/fsq/cppjieba/dict/user.dict.utf8";
const char* const IDF_PATH = "/home/fsq/cppjieba/dict/idf.utf8";
const char* const STOP_WORD_PATH = "/home/fsq/cppjieba/dict/stop_words.utf8";
class SplitTool
{
public:
    SplitTool() 
        :jieba(DICT_PATH,HMM_PATH,USER_DICT_PATH,IDF_PATH,STOP_WORD_PATH){}
    ~SplitTool() {}
    vector<string>  cut(const string & );    
private:
    cppjieba::Jieba jieba;
  
};

 





}//end of wd
