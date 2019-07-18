#include "NotQuery.h"


QueryResult
NotQuery::eval(const TextQuery& text) const{
    //__TRACE("query = %s\n",query.rep().c_str());
    auto result = query.eval(text);
    auto ret_lines =make_shared<set<line_no>>();
    auto beg= result.begin(),end=result.end();
    auto sz=result.get_file()->size();
    for(size_t n=0;n!=sz;++n){
        if(beg==end||*beg!=n){
            ret_lines->insert(n);
        }else if(beg!=end)
            ++beg;
    }
    //__TRACE("lines=%ld\n",ret_lines->size());
    return QueryResult(rep(),ret_lines,result.get_file());
}
