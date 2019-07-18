#pragma once

#include "QueryResult.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <map>
#include <set>
using namespace std;


class QueryResult;
class TextQuery
{
public:
    using line_no=vector<string>::size_type;
    TextQuery(ifstream &);
    QueryResult query(const string &) const;

private:
    shared_ptr<vector<string> > file;  //输入文件

    map<string,shared_ptr<set<line_no>>> wm; // 指向存放行号的set容器

};

