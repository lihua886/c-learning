#pragma once


#include "BinaryQuery.h"
class Query;
class OrQuery
:public BinaryQuery
{
public:
    friend Query operator|(const Query&,const Query&);
    OrQuery(const Query &left,const Query&right)
    :BinaryQuery(left,right,"|"){}//继承类调用基类的构造函数
    QueryResult eval(const TextQuery&)  const;
    //~OrQuery(){}
};

inline Query operator|(const Query&lhs,const Query&rhs){
    return shared_ptr<Query_base>(new OrQuery(lhs,rhs));
}
