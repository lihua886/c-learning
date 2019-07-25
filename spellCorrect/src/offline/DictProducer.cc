
#include "DictProducer.h"
#include "IndexProducer.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <func.h>
using std::ifstream;
using std::ofstream;
using std::istringstream;

namespace wd{
    
void handleLine(string& line){
    for(auto & it:line){
        if(!isalpha(it)){
            it=' ';
        }else{
            it=tolower(it);
        }
    }
}

void DictProducer::readDir(){
    DIR* dir;
    dir=opendir(get_files(string()).c_str());
    struct dirent *p;
    char temp[1024]={0};
    while((p=readdir(dir))!=NULL){
        if(!strcmp(p->d_name,".")||!strcmp(p->d_name,".."))
            continue;
        sprintf(temp,"/%s",p->d_name);
        _files.push_back(get_files(temp));
    }
    closedir(dir);
}
     
DictProducer::DictProducer(const string& dir)
    :_dir(dir){
        readDir();
    }
    //DictProducer(const string& dir, SplitTool   * splitTool)    构造函数,专为中文处理
void DictProducer::build_dict(){
    for(auto &it:_files){
       ifstream ifs(it.c_str());
       string line;
       string word;
       while(std::getline(ifs,line)){
           handleLine(line);
           std::istringstream iss(line);
           while(iss>>word){
              _dict[word]++;             
           }
       }
    }   
   //创建英文字典
}
//void build_cn_dict()    创建中文字典
void DictProducer::store_dict(const char * filepath){
    ofstream ofs(filepath,ofstream::app);
    for(auto &it:_dict){
        ofs<<it.first<<"  "<<it.second<<std::endl;
    }
}  //将词典写入文件
void DictProducer::show_files()const{
    for(auto &it:_files){
        std::cout<<it<<std::endl;
    }
}  //查看文件路径，作为测试用
void DictProducer::show_dict()const{
    for(auto & it:_dict){
        std::cout<<it.first<<"  "<<it.second<<std::endl;
    }
}   //查看词典，作为测试用
string DictProducer::get_files(const string & file){
    string dir1("/home/fsq/study/c++/c-learning/spellCorrect/");
    return dir1+_dir+file;
}    //获取文件的绝对路径

//void DictProducer::push_dict(const string & word){
//         
//} //存储某个单词



}//end of wd
