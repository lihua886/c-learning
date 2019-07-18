#pragma once

#define __TRACE(...) fprintf(stdout, "file[%s]line[%u]func[%s]::",__FILE__,__LINE__,__func__);\
            fprintf(stdout,__VA_ARGS__)
#include <iostream>
#include <memory>
#include <vector>
#include <set>
using namespace std;
class QueryResult// 保存查询结果
{
    friend ostream & print(ostream &,const QueryResult&);
public:
    using line_no=vector<string>::size_type;
    QueryResult(string s,
                shared_ptr<set<line_no>> p,
                shared_ptr<vector<string>> f);
    set<line_no>::iterator begin(){
        return lines->begin();
    }   
    set<line_no>::iterator end(){
        return lines->end();
    }
    shared_ptr<vector<string> >  get_file(){
        return file;
    }
private:
    string sought;  //查询的单词
    shared_ptr<set<line_no> > lines; //  行号
    shared_ptr<vector<string> > file;  // 文本
};


