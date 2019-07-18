#include "OrQuery.h"


QueryResult OrQuery::eval(const TextQuery& text) const{
   //__TRACE("lhs= %s,rhs=%s\n",lhs.rep().c_str(),rhs.rep().c_str());
    auto right=rhs.eval(text),left=lhs.eval(text);
    auto ret_lines=make_shared<set<line_no>>(left.begin(),left.end());
    ret_lines->insert(right.begin(),right.end());
    //__TRACE("lines=%ld\n",ret_lines->size());
    return QueryResult(rep(),ret_lines,left.get_file());
}
