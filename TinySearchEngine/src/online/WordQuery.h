#pragma once
#include "WebPage.h"
#include "Configuration.h"
#include "WordSegmentation.h"


#include <vector>
#include <string>
#include <unordered_map>
#include <set>
#include <map>
using std::map;
using std::vector;
using std::string;
using std::unordered_map;
using std::pair;
using std::set;


namespace wd{
class WordQuery
{
public:
    WordQuery(Configuration & conf);  //  构造函数
    string doQuery(const string & str); //执行查询，返回结果
    void loadLibrary();   // 加载库文件
    vector<double> getQueryWordsWeightVector(vector<string> & queryWords); // 计算查询词的权重值
    bool executeQuery(const vector<string> & queryWords,
                      map<int,vector<double> >  &resultVec
                     );// 执行查询
    string createJson(vector<int> &  docIdVec,const vector<string> & queryWords);    
    string returnNoAnswer();    
private:
    void readWebpageOffset();
    void readInvertIndex();
    vector<string>  cutQuery(const string & str);
    vector<int> executeSort(vector<double> &queryWeights,
                            map<int,vector<double> >  &resultVec);
private:
    Configuration & _conf; // 配置文件的引用
    WordSegmentation _jieba;   //   Jieba分词库对象
    
    std::unordered_map<int,WebPage> _pageLib; //  网页库
    unordered_map<int, pair<int, int> > _offsetLib;// 偏移库
    unordered_map<string, set<pair<int, double>>> _invertIndexTable;// 倒排索引表
};







}//end of wd;




