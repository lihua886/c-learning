#pragma once

#include "BinaryQuery.h"
class Query;
class AndQuery
:public BinaryQuery
{
public:
    friend Query operator&(const Query&,const Query&);
    AndQuery(const Query&left,const Query&right)
        :BinaryQuery(left,right,"&"){}

    QueryResult eval(const TextQuery&) const;

};
inline Query operator&(const Query&lhs,const Query&rhs){
    return shared_ptr<Query_base>(new AndQuery(lhs,rhs));
}
