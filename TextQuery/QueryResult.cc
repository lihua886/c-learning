#include "QueryResult.h"


string make_plural(size_t size,const string&word,const string&ending){
    return size==1?word:(word+ending);
}

ostream & print(ostream & os,const QueryResult &qr){
    //如果找到了单词，打印出现次数和所有出现的位置,没有考虑一行有重复单词的情况
    //__TRACE("qr.lines=%ld\n",qr.lines->size());
    os<<qr.sought<<" occurs "<<qr.lines->size()<<" "
        <<make_plural(qr.lines->size(),"time","s")<<endl;
    for(auto num:*qr.lines){
        os<<"\t(line "<<num+1<<") "<<*(qr.file->begin()+num)<<endl;
    }
    return os;
}
using line_no=vector<string>::size_type;
QueryResult::QueryResult(string s,
                shared_ptr<set<line_no>> p,
                shared_ptr<vector<string>> f)
    :sought(s),lines(p),file(f){}
