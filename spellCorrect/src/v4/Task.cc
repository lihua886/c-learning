#include "Task.h"
#include "Thread.h"
#include "Cache.h"
#include "Dictionary.h"
#include "EditDistance.h"
#include "Connection.h"
#include "CacheManger.h"
#include "str-ws.h"
#include <sstream>
#include <string.h>
#include <cctype>
#include <cwctype>

using std::ostringstream;
#define __TRACE(...) fprintf(stdout, "file[%s]line[%u]func[%s]::",__FILE__,__LINE__,__func__);\
    fprintf(stdout,__VA_ARGS__)
namespace wd{

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
Mytask::Mytask(const std::string & msg,
           const ConnectionPtr & conn)
        : _query(msg)
        , _conn(conn)
        ,_dict(Dictionary::getInstance()->getDict())
        ,_indexTable(Dictionary::getInstance()->getIndex()){
              memset(array,0,50000);
              queryfunc(_query);
          }
void Mytask::process(){
    if(_query.size()==0){
       _conn->sendInLoop("no answer");
       return;
    }
    Cache &mycache=CacheManger::getCache(wd::current_thread::threadnum);
 //   size_t size=CacheManger::getCache(wd::current_thread::threadnum).getSize();
  //  __TRACE("%ld,myche.size()=%ld,size=%ld\n",wd::current_thread::threadnum,mycache.getSize(),size);
    if(!searchCache(mycache)){
       taskCore();
       if(_que.empty()){
          _conn->sendInLoop("no answer");
          return;
       }
       Json::Value root;
       changeJson(root);
  //  __TRACE("_query=%s,res=%s\n",_query.c_str(),root.toStyledString().c_str());
      mycache.addElement(_query,root.toStyledString());
      _conn->sendInLoop(root.toStyledString());
    }
}
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
#if 1
bool Mytask::searchCache(Cache & mycache){
    string res=mycache.getElement(_query);
    if(res.size()!=0){
       __TRACE("word %s in cache\n ",_query.c_str());
        _conn->sendInLoop(res);
        return true;
    }else{
       __TRACE("word %s not in cache\n ",_query.c_str());
        return false;
    }
}
#endif
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




