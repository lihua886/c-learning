#include "WebPage.h"
#include "Configuration.h"
#include "WordSegmentation.h"
#include "str-ws.h"
#include <stdlib.h>
#include <iostream>
#include <regex>
#include <cctype>
#include <algorithm>
#include <sstream>
using std::istringstream;
using std::cout;
using std::endl;
using std::sort;
using std::pair;
using std::find;

namespace  wd{

//  构造函数 
bool numberJudge(const string & words){
    for(auto &it:words){
        if(isalnum(it)){
            return true;
        }
    }
    return false;
}


WebPage::WebPage(const string & doc)
       :_doc(doc){

}
#if 1
WebPage::WebPage(const WebPage & rhs)
    :_doc(rhs._doc)
    ,_docId(rhs._docId)
    ,_docUrl(rhs._docUrl)
    ,_docContent(rhs._docContent)
    ,_docSummary(rhs._docSummary)
    ,_topWords(rhs._topWords.begin(),rhs._topWords.end())
    ,_wordsMap(rhs._wordsMap.begin(),rhs._wordsMap.end()){
    }
#endif
//  对格式化文档进行处理  

void WebPage::processDoc(Configuration & _conf,
                         WordSegmentation & _jieba){
    _docId=::atoi(parse("docid").c_str());
    _docUrl=parse("url");
    _docTitle=parse("title");
    _docContent=parse("content");
#if 1
    std::wstring ws=s2Ws(_docContent);
    std::wregex regex(L"[^\u4e00-\u9fa5]");
    ws=std::regex_replace(ws,regex,L"");
    string newstr=ws2S(ws);
#endif
#if 0
    std::regex regex("^[\u4e00-\u9fa5a-zA-Z0-9]");
    string content=std::regex_replace(_docContent,regex,"");
    void processDoc();   //  对格式化文档进行处理
#endif
    vector<string> words=_jieba.cut(newstr);
    set<string> _stopdict=_conf.getStopWords();
    for(auto &it:words){
        if(!numberJudge(it)){
            auto iter=_stopdict.find(it);
            if(iter==_stopdict.end()){
                _wordsMap[it]++;    
            }
        }
    }
}
string WebPage::parse(const string &attr){
    string::size_type n1,n2;
    n1=_doc.find(string("<").append(attr).append(">"))+string("<").append(attr).append(">").size();
    n2=_doc.find(string("</").append(attr).append(">"));
    string str=_doc.substr(n1,n2-n1);
    return str;
}
//  求取文档的topk词集 
void WebPage::calcTopK(){
    set<pair<string,int>,Compare>  myset(_wordsMap.begin(),_wordsMap.end());
    int i=0;
    for(auto iter=myset.begin();i<TOPK_NUMBER&&iter!=myset.end();++i,++iter){
        _topWords.emplace_back(iter->first);
       // cout<<iter->first<<": "<<iter->second<<endl;
    }
} 

void WebPage::print(){
    cout<<"docid= "<<_docId<<endl;
    cout<<"docurl= "<<_docUrl<<endl;
    cout<<"doctitle= "<<_docTitle<<endl;
   // cout<<"docContent= "<<_docContent<<endl;
#if 0
    cout<<"top 10 words= "<<endl;
    for(auto &it:_topWords){
        cout<<it<<" ";
    }
    cout<<endl;
#endif
}
string WebPage::getSummary(const vector<string>& queryword){
       std::istringstream iss(_docContent);
       std::string::size_type n,n2,n3;
       vector<string> summary;
       string line;
       while(std::getline(iss,line)){
            for(auto &it:queryword){
                n=line.find(it);
                if(n!=std::string::npos){
                    string linebegin=line.substr(0,n);
                    string linelast=line.substr(n);
                    n2=linebegin.rfind("。");
                    if(n2!=std::string::npos){
                       linebegin=linebegin.substr(n2+3);
                    }
                    n3=linelast.find("。");
                    if(n3!=std::string::npos){
                       linelast=linelast.substr(0,n3); 
                    }
                    line=linebegin+linelast;
                    summary.emplace_back(line);
                    break;
                }
            }
            if(summary.size()>5){
                break;
            }
       }
       string mysummary;
       for(auto &it:summary){
           mysummary.append(it).append("\n");
       }
       return mysummary;
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
    size_t lhsSize=lhs._topWords.size();
    size_t rhsSize=rhs._topWords.size();
    size_t commonSize=lhsSize<rhsSize?lhsSize:rhsSize;
    if(static_cast<double>(cnt/commonSize)>0.6){
        return true;
    }else{
        return false;
    }
}
// 对文档按Docid进行排序
bool operator < (const WebPage & lhs,const WebPage & rhs){
        return lhs._docId<rhs._docId;
}  













}//end of wd
