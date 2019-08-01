#include "PageLibPreprocessor.h"
#include "Configuration.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string.h>
#include <algorithm>
#include <cmath>
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::istringstream;
using std::sort;
using std::find;



namespace  wd{



PageLibPreprocessor::PageLibPreprocessor(Configuration& conf,WordSegmentation & jieba)
    :_conf(conf),_jieba(jieba){}//  构造函数


// 执行预处理 
void PageLibPreprocessor::doProcess(){
    for(auto &it:_pageLib){
        it.processDoc(_conf,_jieba);
//        it.print();
        it.calcTopK();
    }
    _pageLib[197].print();
    _pageLib[203].print();

    
}   
//  根据配置信息读取网页库和位置偏移库的内容 
void PageLibPreprocessor::readInfoFromFile(){
    ifstream ifs_offset(_conf.getConfigMap()["offsetlib"]);
    ifstream ifs_text(_conf.getConfigMap()["webpagelib"]);
    string line;
    int id,beginSit,txtlength;
    while(std::getline(ifs_offset,line)){
        std::istringstream iss(line);
        iss>>id>>beginSit>>txtlength;
        //       cout<<id<<" "<<beginSit<<" "<<txtlength<<endl;
        // _offsetLib[id]=std::make_pair(beginSit,txtlength);
        ifs_text.seekg(beginSit,ifs_text.beg);
        char buf[65536]={0};
        ifs_text.read(buf,txtlength);
        //      cout<<strlen(buf)<<endl;
        WebPage wb(buf);
        _pageLib.emplace_back(wb);
    }
}
//  对冗余的网页进行去重 
void PageLibPreprocessor::cutRedundantPages(){
    for(size_t i=0;i!=_pageLib.size();++i){
        for(size_t j=i+1;j!=_pageLib.size();++j){
            if(_pageLib[i]==_pageLib[j]){
                _pageLib[j]=_pageLib[_pageLib.size()-1];
                _pageLib.pop_back();
                --j;
            }
        }
    }
    //cout<<_pageLib.size()<<endl;
}  

//   创建倒排索引表  
void PageLibPreprocessor::buildInvertIndexTable(){
    buildWordsTextTAble();//记录单词在哪些文档中出现
    for(size_t k=0;k!=_pageLib.size();++k){
        int docId=_pageLib[k].getDocId();
        std::unordered_map<string,double>  weights;
        double total=calculateWeight(k,weights);
        for(auto &ans:weights){
            double wReal=ans.second/sqrt(total);
            
            _invertIndexTable[ans.first].insert(std::make_pair(docId,wReal));
        }
    }
#if 0
    for(auto &it:_invertIndexTable){
        cout<<it.first<<" ";
        for(auto &i:it.second){
            cout<<i.first<<" "<<i.second<<" ";
        }
        cout<<endl;
    }
#endif
} 
double PageLibPreprocessor::calculateWeight(int k,std::unordered_map<string,double> &weights){
    std::map<string,int> tmpmap=_pageLib[k].getWordsMap();
    double total;
    for(auto &it:tmpmap){
        int TF=it.second;
        int DF=_WordsInTextTable[it.first].size();
        int N=_pageLib.size();
        double IDF=log(static_cast<double>(N)/(DF+1))/log(2);
        double w=IDF*TF;
        total=total+w*w;
        weights[it.first]=w;
    }
    return total;
}
void PageLibPreprocessor::buildWordsTextTAble(){
    for(auto &it:_pageLib){
       int docId=it.getDocId();
       map<string,int> tmpmap=it.getWordsMap();
       for(auto &ans:tmpmap){
           _WordsInTextTable[ans.first].push_back(docId);
       }
    }
#if 0
    for(auto &it:_WordsInTextTable){
        cout<<it.first<<" ";
        for(auto &i:it.second){
            cout<<i<<" ";
        }
        cout<<endl;
    }
#endif
}

// 将经过预处理之后的网页库、位置偏移库和倒排索引表写回到磁盘上 
void PageLibPreprocessor::storeOnDisk(){
    storeWebOffset();
    storeInvertIndex();
} 
void PageLibPreprocessor::storeWebOffset(){
    ofstream ofs_offset(_conf.getConfigMap()["offsetlib"]);
    ofstream ofs_text(_conf.getConfigMap()["webpagelib"]);
    for(auto &it:_pageLib){
        int docid=it.getDocId();
        string doc=it.getDoc();
        long beginSit=ofs_text.tellp();
        ofs_text<<doc;
        ofs_offset<<docid<<" "<<beginSit<<" "<<doc.size()<<endl;
    }
}
void PageLibPreprocessor::storeInvertIndex(){
    ofstream ofs_invertindex(_conf.getConfigMap()["invertindex"]);
    for(auto &it:_invertIndexTable){
        ofs_invertindex<<it.first<<" ";
        for(auto &ans:it.second){
            ofs_invertindex<<ans.first<<" "<<ans.second<<"  ";
        }
        ofs_invertindex<<endl;
    }
}







}// end of wd;
