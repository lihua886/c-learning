#pragma once
#include <json/json.h>
#include <string>
#include <memory>
#include <queue>
#include <vector>
#include <unordered_map>
#include <set>

namespace  wd{
struct MyResult
{
    int distance;
    std::string  candidate_word;
    int frequency;
};
struct compareResult{
    bool operator()(const MyResult& lhs,const MyResult& rhs) const{
        if(lhs.distance!=rhs.distance){
            return lhs.distance>rhs.distance;
        }else if(lhs.frequency!=rhs.frequency){
            return lhs.frequency<rhs.frequency;
        }else{
            return lhs.candidate_word>rhs.candidate_word;
        }
    }
};

class Connection;
class Cache;
using ConnectionPtr=std::shared_ptr<Connection>;
class Mytask
{
public:
    Mytask(const std::string & msg,
           const ConnectionPtr & conn);

    //运行在线程池的某一个子线程中
    void process();
private:
    int calcDistance(std::string & rhs);
    void taskCore();
    void changeJson(Json::Value &);
    bool searchCache(Cache &);
private:
    std::string _query;
    ConnectionPtr _conn;
    bool array[50000];
    std::vector<std::pair<std::string, int>>  &_dict;
    std::unordered_map<std::string, std::set<int>> &_indexTable;
    std::priority_queue<MyResult,std::vector<MyResult>,compareResult> _que;
};

}
