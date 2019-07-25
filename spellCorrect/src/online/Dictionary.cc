#include "Dictionary.h"
#include <fstream>
#include <sstream>
#include <iostream>
using std::cout;
using std::endl;
using std::istringstream;
using std::ifstream;


namespace wd{
Dictionary * Dictionary::_pInstance=nullptr;


void Dictionary::readDictFile(const string & file){
    ifstream ifs(file);
    string line;
    string word;
    int number;
    while(std::getline(ifs,line)){
        std::istringstream iss(line);
        iss>>word>>number;
        _dict.emplace_back(std::make_pair(word,number));
    }
}
void Dictionary::readIndexFile(const string & file){
    ifstream ifs(file);
    string line;
    string inx;
    int num;
    while(std::getline(ifs,line)){
        std::istringstream iss(line);
        iss>>inx;
        while(iss>>num){
            _indexTable[inx].insert(num-1);
        }
    }
}
void Dictionary::show_dict(){
    for(auto & it:_dict){
        std::cout<<it.first<<"  "<<it.second<<std::endl;
    }
}

void Dictionary::show_index(){
    for(auto & it:_indexTable){
        std::cout<<it.first<<":";
        for(auto & it1:it.second){
            cout<<it1<<" ";
        }
        cout<<endl;
    }     
}

}// end of wd
