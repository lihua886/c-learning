#pragma once
#include <string>
#include <map>
#include <vector>
#include <unordered_map>
#include <memory>
using std::vector;
using std::map;
using std::string;
using std::unordered_map;
using std::wstring;
using std::unique_ptr;

namespace  wd{
class SplitTool;
class DictProducer
{
//主要的函数成员：
public:
    DictProducer(const string& dir);
    DictProducer(const string& dir, SplitTool *   splitTool);   // 构造函数,专为中文处理
    void build_dict();   //创建英文字典
    void build_cn_dict();  //  创建中文字典
    void store_dict(const char * filepath);  //将词典写入文件
    void show_files()const;  //查看文件路径，作为测试用
    void show_dict()const;   //查看词典，作为测试用
    string get_files(const string &);    //获取文件的绝对路径
    void push_dict(const string & word); //存储某个单词
private:
    void readDir();
    void build_stopdict();
private:
    string _dir;            //语料库文件存放路径
    vector<string> _files;  // 语料库文件的绝对路径集合
    map<string,int> _dict;
    unordered_map<string,int> _stopdict;//  配置文件内容
    SplitTool * _splitTool;
};




}// end of wd
