#include "AndQuery.h"
#include "algorithm"

QueryResult AndQuery::eval(const TextQuery& text) const{
   //__TRACE("lhs= %s,rhs=%s\n",lhs.rep().c_str(),rhs.rep().c_str());
   auto left=lhs.eval(text),right=rhs.eval(text);
   auto ret_lines=make_shared<set<line_no>>();
   set_intersection(left.begin(),left.end(),\
                    right.begin(),right.end(),\
                    inserter(*ret_lines,ret_lines->begin()));
   //__TRACE("lines= %ld\n",ret_lines->size());
   return QueryResult(rep(),ret_lines,left.get_file());
}

