#include "IndexProducer.h"
#include "str-ws.h"
#include <fstream>
#include <sstream>
#include <iostream>
using std::ofstream;
using std::ostringstream;
using std::istringstream;
using std::ifstream;
namespace  wd{

void IndexProducer::readDict(){
    ifstream ifs("/home/fsq/study/c++/c-learning/spellCorrect/data/en/mydict.dat");
    string line;
    while(getline(ifs,line)){
        std::istringstream iss(line);
        string key;
        int num;
        iss>>key>>num;
        _dict[key]=num;
    }
}

void IndexProducer::build_index(){
    int k=1;
    for(auto &it:_dict){
        for(auto & i:it.first){
            std::ostringstream oss;
            oss<<i;
            _index[oss.str()].insert(k);
        }
        ++k;
    }
}
void IndexProducer::build_cnindex(){
    int k=1;
    for(auto &it:_dict){
        std::wstring ws=s2Ws(it.first);
        for(auto & i:ws){
            std::wstring ws2;
            ws2.push_back(i);
            string word=ws2S(ws2);
            _index[word].insert(k);
        }
        ++k;
    }
}
void IndexProducer::store_index(const char* path){
    ofstream ofs(path,std::ofstream::app);
    for(auto &it:_index){
        ofs<<it.first<<" ";
        for(auto &it1:it.second){
            ofs<<it1<<" ";
        }
        ofs<<std::endl;
    }
}




}// end of wd

