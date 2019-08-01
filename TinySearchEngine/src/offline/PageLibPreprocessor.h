#pragma once
#include "WebPage.h"
#include <string>
#include <unordered_map>
#include <vector>
using std::vector;
using std::pair;
using std::string;
using std::unordered_map;



namespace wd{

class Configuration;
class WordSegmentation;
class PageLibPreprocessor
{
public:
    PageLibPreprocessor(Configuration& ,WordSegmentation &);  //  构造函数
    void doProcess() ;  // 执行预处理
    void readInfoFromFile();//  根据配置信息读取网页库和位置偏移库的内容
    void cutRedundantPages();  //  对冗余的网页进行去重
    void buildInvertIndexTable(); //   创建倒排索引表
    void storeOnDisk(); // 将经过预处理之后的网页库、位置偏移库和倒排索引表写回到磁盘上
private:
    void buildWordsTextTAble();
    double calculateWeight(int ,std::unordered_map<string,double> &);
    std::unordered_map<string,vector<int> >  _WordsInTextTable;
    void storeWebOffset();
    void storeInvertIndex();
private:
    Configuration & _conf;//   配置文件对象的引用
    WordSegmentation & _jieba; //    分词对象
    vector <WebPage> _pageLib; //  网页库的容器对象
    unordered_map<int, pair<int, int> >  _offsetLib;  //   网页偏移库对象
    unordered_map<string, set<pair<int, double> > > _invertIndexTable; // 倒排索引表对象
};



}// end of wd;
