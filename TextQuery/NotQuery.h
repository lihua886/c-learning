#pragma once

#include "Query.h"
class Query;
class NotQuery
:public Query_base
{
public:
    friend Query operator~(const Query &);
    NotQuery(const Query &q):query(q){}
    string rep() const {
        return "~("+query.rep()+")";
    }

    QueryResult eval(const TextQuery&) const ;
    Query query;
};

inline Query operator~(const Query &operand){
    return shared_ptr<Query_base>(new NotQuery(operand));
}

