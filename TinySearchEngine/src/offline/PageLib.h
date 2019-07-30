#pragma once

#include <vector>
#include <map>
#include <string>
using std::map;
using std::vector;
using std::string;
using std::pair;

namespace wd{

struct RssItem{
    string title;
    string link;
    string description;
    string content;
};
class Configuration;
class DirScanner;
class PageLib
{
public:

    PageLib(Configuration& conf,DirScanner & dirScanner)
        :_conf(conf),_dirScanner(dirScanner){}//  构造函数
    void create(); //  创建网页库
    void store();  //  存储网页库和位置偏移库
private:
    void  RssItemFunc(const RssItem & item,long index);
private:
    Configuration & _conf;  // 配置文件对象的引用
    DirScanner & _dirScanner;  //  目录扫描对象的引用
    vector<string> _vecFilesfiles; // 存放格式化之后的网页的容器
    map<int, pair<int, int> > _offsetLib; //   存放每篇文档在网页库的位置信息


};




}//end of wd

    
