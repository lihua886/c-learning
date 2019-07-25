#include "Task.h"
#include "Dictionary.h"
#include "EditDistance.h"
#include "Connection.h"
#include <sstream>
#include <string.h>
using std::ostringstream;

namespace wd{
Mytask::Mytask(const std::string & msg,
           const ConnectionPtr & conn)
        : _query(msg)
        , _conn(conn)
        ,_dict(Dictionary::getInstance()->getDict())
        ,_indexTable(Dictionary::getInstance()->getIndex()){
              memset(array,0,50000);
          }
void Mytask::process(){
    taskCore();    
    string response;
    int cnt=3;
    while(cnt--){
        response.append(_que.top().candidate_word).append("  ");
        _que.pop();    
    }
    _conn->sendInLoop(response);
}

int Mytask::calcDistance(std::string & rhs){
    return editDistance(_query,rhs);
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
