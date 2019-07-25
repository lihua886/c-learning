#include "Task.h"
#include "Thread.h"
#include "Cache.h"
#include "Dictionary.h"
#include "EditDistance.h"
#include "Connection.h"
#include "CacheManger.h"
#include <sstream>
#include <string.h>

using std::ostringstream;
#define __TRACE(...) fprintf(stdout, "file[%s]line[%u]func[%s]::",__FILE__,__LINE__,__func__);\
    fprintf(stdout,__VA_ARGS__)
namespace wd{
Mytask::Mytask(const std::string & msg,
           const ConnectionPtr & conn)
        : _query(msg)
        , _conn(conn)
        ,_dict(Dictionary::getInstance()->getDict())
        ,_indexTable(Dictionary::getInstance()->getIndex()){
              memset(array,0,50000);
              _query.erase(_query.end()-1);
          }
void Mytask::process(){
    Cache mycache=CacheManger::getInstance()->getCache(wd::current_thread::threadnum);
    __TRACE("%ld\n",wd::current_thread::threadnum);
    if(!searchCache(mycache)){
       taskCore();
       __TRACE("calulate distance\n");
       Json::Value root;
       changeJson(root);
       mycache.addElement(_query,root.toStyledString());
       _conn->sendInLoop(root.toStyledString());
       __TRACE("send message finish\n");
    }
    __TRACE("finish task\n");
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
bool Mytask::searchCache(Cache & mycache){
    string res=mycache.getElement(_query);
    if(res.size()!=0){
        _conn->sendInLoop(res);
        return true;
    }else{
        return false;
    }
}
void Mytask::taskCore(){
    for(auto & it:_query){
        std::ostringstream oss;
        oss<<it;
        auto iter=_indexTable.find(oss.str());
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
