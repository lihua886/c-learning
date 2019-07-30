#pragma once

#include <string>
#include <map>
#include <vector>
#include <set>
using std::set;
using std::vector;
using std::map;
using std::string;
using std::pair;



namespace  wd{
struct Compare{
    bool operator()(const pair<string,int> &lhs,const pair<string,int> &rhs) const{
        return lhs.second>rhs.second;
    }
};
class Configuration;
class WordSegmentation;
class WebPage
{
public:
    WebPage(const  string & doc,Configuration & config,
            WordSegmentation & jieba); //  构造函数
    
    
    int getDocId(){ return _docId; } // 获取文档的docid
    string getDoc(){return _doc;}  // 获取文档
    map<string, int> & getWordsMap(){return _wordsMap;}  //  获取文档的词频统计map
    
    
    void processDoc();   //  对格式化文档进行处理
    void calcTopK();    // 求文档的TopK单词
    //友元函数：
    friend bool operator==(const WebPage & lhs,const WebPage & rhs);    // 判断两篇文档是否相等
    friend bool operator < (const WebPage & lhs,const WebPage & rhs);   // 对文档按Docid进行排序
private:
    string parse(const string &attr);
private:
    Configuration & _conf;
    WordSegmentation & _jieba;
    const static int TOPK_NUMBER = 10;  
    string _doc;   // 整篇文档，包含xml在内
    int _docId;    // 文档id
    string _docTitle;  // 文档标题
    string _docUrl;// 文档URL
    string _docContent;// 文档内容
    string _docSummary;// 文档摘要，需自动生成，不是固定的
    vector<string> _topWords; // 词频最高的前20个词
    map<string,int> _wordsMap; // 保存每篇文档的所有词语和词频，不包括停用词
};



}//end of wd;
