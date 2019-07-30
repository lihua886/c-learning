#pragma once

#include <vector>
#include <string>
using std::string;
using std::vector;




namespace  wd{
class Configuration;
class DirScanner
{
public:
    DirScanner(Configuration & conf)
    :_conf(conf){}
    ~DirScanner() {}
    void operator()();
    void print() const;// 打印作为测试
private:
    void traverse(const string &);
private:
    vector<string> _files;
    Configuration & _conf;
};







}//end of wd
