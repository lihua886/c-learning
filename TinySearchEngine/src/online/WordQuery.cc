#include "WordQuery.h"    
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <json/json.h>
using std::cout;
using std::endl;
using std::count;
using std::istringstream;
using std::ifstream;







namespace wd{


struct cmp{
    bool operator()(const pair<int,double>& lhs,const pair<int,double>& rhs) const{
        return lhs.second>rhs.second;
    }
};

WordQuery::WordQuery(Configuration & conf)
        :_conf(conf){}  //  构造函数

        
        
//执行查询，返回结果  
string WordQuery::doQuery(const string & str){
    vector<string> queryWords=cutQuery(str);
    //打印queryword信息
#if 1
    for(auto &it:queryWords){
        cout<<it<<" ";
    }
    cout<<endl;
#endif
    vector<double> QueryWeight=getQueryWordsWeightVector(queryWords);
#if 1
    for(auto &it:queryWords){
        cout<<it<<" ";
    }
    cout<<endl;
#endif
    map<int,vector<double> > resultVec;
    if(executeQuery(queryWords,resultVec)){
      vector<int> docIdVec=executeSort(QueryWeight,resultVec);
#if 1
    for(auto &it:docIdVec){
        cout<<it<<" ";
    }
    cout<<endl;
#endif
      return createJson(docIdVec,queryWords);
    }else{
        return returnNoAnswer();
    }
} 


// 加载库文件 
void WordQuery::loadLibrary(){
    readWebpageOffset();
    readInvertIndex();
} 

void WordQuery::readWebpageOffset(){
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
        
        wb.processDoc(_conf,_jieba);
        _pageLib[wb.getDocId()]=wb;
    }
}
void WordQuery::readInvertIndex(){
   ifstream ifs(_conf.getConfigMap()["invertindex"]); 
   string line;
   while(std::getline(ifs,line)){
        istringstream iss(line);
        string key;
        iss>>key;
        int docid;double weight; 
        while(iss>>docid>>weight){
            _invertIndexTable[key].insert(std::make_pair(docid,weight));
        }
   }
}
vector<string>  WordQuery::cutQuery(const string & str){
    return _jieba.cut(str);
}
// 计算查询词的权重值 
vector<double> WordQuery::getQueryWordsWeightVector(vector<string> & queryWords){
    vector<double>  weights;
    double total=0;
    for(auto &it:queryWords){
        int TF=count(queryWords.begin(),queryWords.end(),it);
        int DF=_invertIndexTable[it].size();
        int N=_pageLib.size();
        double IDF=log(N/(DF+1))/log(2);
        double w=IDF*TF;
        total=total+w*w;
        weights.push_back(w);
    }
    for(size_t i=0;i!=weights.size();++i){
        weights[i] /=sqrt(total);
        cout<<"i= "<<i<<"-->weight[i]="<<weights[i]<<endl;
    }
    return weights;
}


// 执行查询 
bool WordQuery::executeQuery(const vector<string> & queryWords,
                      map<int,vector<double> >  &resultVec
                      ){
    for(auto &it:queryWords){
        for(auto &ans:_invertIndexTable[it]){
            resultVec[ans.first].push_back(ans.second);
        }
    }
    for(auto iter=resultVec.begin();iter!=resultVec.end();++iter){
        if(iter->second.size()!=queryWords.size()){
            resultVec.erase(iter);
        }
    }
#if 1
    for(auto &it:resultVec){
        cout<<it.first<<"-->";
        for(auto &i:it.second){
            cout<<i<<" ";
        }
        cout<<endl;
    }
#endif
    if(resultVec.size()){
        return true;
    }else{
        return false;
    }
}
vector<int>  WordQuery::executeSort(vector<double> &queryWeights,
                            map<int,vector<double> >  &resultVec){
    set<pair<int,double>,cmp>  cosSet; 
    double s1=0,s2=0,s=0;
    for(auto &it:resultVec){
        vector<double> tmp=it.second;
        cout<<"切分的单词个数: "<<tmp.size()<<endl;
        for(size_t j=0;j!=tmp.size();++j){
            s += queryWeights[j]*queryWeights[j];
            s1 += tmp[j]*tmp[j];
            s2 += queryWeights[j]*tmp[j];
        }
        s =sqrt(s);
        s1=sqrt(s1);
        double result=s2/(s*s1);
        cosSet.insert(std::make_pair(it.first,result));
    }
#if 1
    for(auto &it:cosSet){
        cout<<it.first<<"-->"<<it.second<<endl;
    }
#endif
    vector<int> docId;
    for(auto &it:cosSet){
        docId.push_back(it.first);
    }
    return docId;
} 


string WordQuery::createJson(vector<int> & docIdVec,const vector<string> & queryWords){   
    Json::Value root;
    Json::Value arr;
    int cnt=0;
    for(auto &it:docIdVec){
        Json::Value v;
        string title=_pageLib[it].getTitle();
        string summary=_pageLib[it].getSummary(queryWords);
        string url=_pageLib[it].getUrl();
        v["title"]=title;
        v["summary"]=summary;
        v["url"]=url;
        arr.append(v);
        if(++cnt>100){
            break;
        }
    }
    root["files"]=arr;
    //cout<<root.toStyledString()<<endl;
    return root.toStyledString();
}    

string WordQuery::returnNoAnswer(){
    Json::Value v;
    string title="not find";
    string summary="empty";
    string url="not find ";
    v["title"]=title;
    v["summary"]=summary;
    v["url"]=url;
    return v.toStyledString();
} 






}//end of wd    
