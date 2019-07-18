#pragma once
#define __TRACE(...) fprintf(stdout, "file[%s]line[%u]func[%s]::",__FILE__,__LINE__,__func__);\
            fprintf(stdout,__VA_ARGS__)
#include "QueryResult.h"
#include "TextQuery.h"
#include <iostream>
using namespace std;
class Query_base
{
    friend class Query;
protected:
    using line_no =TextQuery::line_no;
    virtual  ~Query_base()=default;

private:
    virtual QueryResult eval(const TextQuery&) const=0;
    virtual std::string rep() const=0;
};

