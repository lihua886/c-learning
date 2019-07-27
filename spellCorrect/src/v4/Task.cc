#include "Task.h"
#include "Thread.h"
#include "Cache.h"
#include "Dictionary.h"
#include "EditDistance.h"
#include "Connection.h"
#include "CacheManger.h"
#include "Mylogger.h"
#include "str-ws.h"
#include <sstream>
#include <string.h>
#include <cctype>
#include <cwctype>

using std::ostringstream;
namespace wd{
//对查询词的简单处理
void queryfunc(string & _query){
    _query.erase(_query.end()-1);
    std::wstring ws=s2Ws(_query);
    for(auto &it:ws){
        if(iswalpha(it)){
            it=towlower(it);
        }
    }
    _query=ws2S(ws);
}
//构造函数
Mytask::Mytask(const std::string & msg,
           const ConnectionPtr & conn)
        : _query(msg)
        , _conn(conn)
        ,_dict(Dictionary::getInstance()->getDict())
        ,_indexTable(Dictionary::getInstance()->getIndex()){
              memset(array,0,50000);
              queryfunc(_query);
          }
//线程执行的任务
void Mytask::process(){
    if(_query.size()==0){
       _conn->sendInLoop("no answer");
       return;
    }
    Cache &mycache=CacheManger::getCache(wd::current_thread::threadnum);
    LogInfo("%ld thread search %d client's word: %s\n",wd::current_thread::threadnum,_conn->getclientfd(),_query.c_str());
    if(!searchCache(mycache)){
       taskCore();
       if(_que.empty()){
          _conn->sendInLoop("no answer");
          return;
       }
       Json::Value root;
       changeJson(root);
       mycache.addElement(_query,root.toStyledString());//添加到缓存
       _conn->sendInLoop(root.toStyledString());
    }
}
//转换为json格式
void Mytask::changeJson(Json::Value &root){
    Json::FastWriter fast;
    int cnt=3;
    while(cnt--){  
        string str=_que.top().candidate_word;
        _que.pop();
        root[_query.c_str()].append(str.c_str());
    }
    //std::cout<<fast.write(root)<<std::endl;
}
int Mytask::calcDistance(std::string & rhs){
    return editDistance(_query,rhs);
}
//在缓存中查找
bool Mytask::searchCache(Cache & mycache){
    string res=mycache.getElement(_query);
    if(res.size()!=0){
       LogInfo("%ld thread search %d client's word %s in cache\n",wd::current_thread::threadnum,_conn->getclientfd(),_query.c_str());
        _conn->sendInLoop(res);
        return true;
    }else{
       LogInfo("%ld thread search %d client's word %s not in cache\n",wd::current_thread::threadnum,_conn->getclientfd(),_query.c_str());
        return false;
    }
}
//在词典中查找
void Mytask::taskCore(){
    std::wstring ws=s2Ws(_query);
    for(auto &it:ws){
        wstring tempws(1,it);
        string str=ws2S(tempws);
        auto iter=_indexTable.find(str);
        if(iter!=_indexTable.end()){
            for(auto &num:iter->second){
               if(array[num]){
                   continue;
               }
               MyResult myresult;
               myresult.candidate_word=_dict[num].first;
               myresult.frequency=_dict[num].second;
               myresult.distance=calcDistance(myresult.candidate_word);
               _que.push(myresult);
               array[num]=1;
            }
        }else{
            continue;
        }
    }
}



}




