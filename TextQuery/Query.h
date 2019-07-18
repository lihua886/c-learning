#pragma once

#include "Query_base.h"
#include "WordQuery.h"
#include <memory>
#include <stack>
#include <queue>
#include <map>
#include <cctype>
#include <algorithm>
using namespace std;


class Query
{
    friend Query operator~(const Query &);
    friend Query operator|(const Query &,const Query &);
    friend Query operator&(const Query &,const Query &);
public:
    Query(const string&); // 创建一个新的WordQuery
    Query(){}

    friend bool expChange(string & );
    QueryResult eval(const TextQuery & t) const{
        return q->eval(t);
    }
    string rep() const{
        return q->rep();
    }


private:
    Query(shared_ptr<Query_base> query):q(query){}
    shared_ptr<Query_base> q; //基类指针
};
inline 
Query::Query(const string &s)
    :q(new WordQuery(s)){
 //       __TRACE("s=%s\n",s.c_str());
    }
