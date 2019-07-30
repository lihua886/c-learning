#include "WebPage.h"
#include "Configuration.h"
#include "WordSegmentation.h"
#include "str-ws.h"
#include <stdlib.h>
#include <iostream>
#include <regex>
#include <algorithm>
using std::cout;
using std::endl;
using std::sort;
using std::pair;
using std::find;

namespace  wd{

//  构造函数 
WebPage::WebPage(const string & doc,Configuration & config,
        WordSegmentation & jieba)
       :_conf(config)
       ,_jieba(jieba)
       ,_doc(doc){

} 
//  对格式化文档进行处理  
void WebPage::processDoc(){
    _docId=::atoi(parse("docid").c_str());
    _docUrl=parse("url");
    _docTitle=parse("title");
    _docContent=parse("content");
    std::wstring ws=s2Ws(_docContent);
    std::wregex regex(L"[^\u4e00-\u9fa5]");
    ws=std::regex_replace(ws,regex,L"");
    string newstr=ws2S(ws);
    vector<string> words=_jieba.cut(newstr);
    set<string> _stopdict=_conf.getStopWords();
    for(auto &it:words){
        auto iter=_stopdict.find(it);
        if(iter==_stopdict.end()){
            _wordsMap[it]++;    
        }
    }
}  
string WebPage::parse(const string &attr){
    string::size_type n1,n2;
    n1=_doc.find(string("<").append(attr).append(">"))+string("<").append(attr).append(">").size();
    n2=_doc.find(string("</").append(attr).append(">"));
    string str=_doc.substr(n1,n2);
    return str;
}
//  求取文档的topk词集 
void WebPage::calcTopK(){
    set<pair<string,int>,Compare>  myset(_wordsMap.begin(),_wordsMap.end());
    int i=0;
    for(auto iter=myset.begin();i<TOPK_NUMBER&&iter!=myset.end();++i,++iter){
        _topWords.emplace_back(iter->first);    
    }
} 

//友元函数：
// 判断两篇文档是否相等  
bool operator==(const WebPage & lhs,const WebPage & rhs){
    int cnt=0;
    for(auto &it:lhs._topWords){
        auto iter=find(rhs._topWords.begin(),rhs._topWords.end(),it);
        if(iter!=rhs._topWords.end()){
            cnt++;
        }
    }
    return cnt>6;
}   
// 对文档按Docid进行排序
bool operator < (const WebPage & lhs,const WebPage & rhs){
    return lhs._docId<rhs._docId;
}  













}//end of wd
