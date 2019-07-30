#include "PageLibPreprocessor.h"
#include "Configuration.h"
#include <fstream>
#include <sstream>
using std::ifstream;
using std::istringstream;





namespace  wd{






PageLibPreprocessor::PageLibPreprocessor(Configuration& conf,WordSegmentation & jieba)
    :_conf(conf),_jieba(jieba){}//  构造函数


// 执行预处理 
void PageLibPreprocessor::doProcess(){
    
}   

//  根据配置信息读取网页库和位置偏移库的内容 
void PageLibPreprocessor::readInfoFromFile(){
    ifstream ifs_offset(_conf.getConfigMap()["offsetlib"]);
    ifstream ifs_text(_conf.getConfigMap()["WebPage"]);
    string line;
    int id,beginSit,txtlength;
    while(std::getline(ifs_offset,line)){
        std::istringstream iss(line);
        iss>>id>>beginSit>>txtlength;
       // _offsetLib[id]=std::make_pair(beginSit,txtlength);
        ifs_text.seekg(beginSit,ifs_text.beg);
        char buf[65536]={0};
        ifs_text.read(buf,txtlength);
        WebPage wb(buf,_conf,_jieba);
        _pageLib.emplace_back(std::move(wb));
    }
}
//  对冗余的网页进行去重 
void PageLibPreprocessor::cutRedundantPages(){

}  

//   创建倒排索引表  
void PageLibPreprocessor::buildInvertIndexTable(){

} 
// 将经过预处理之后的网页库、位置偏移库和倒排索引表写回到磁盘上 
void PageLibPreprocessor::storeOnDisk(){

} 



vector <WebPage> _pageLib; //  网页库的容器对象
unordered_map<int, pair<int, int> >  _offsetLib;  //   网页偏移库对象
unordered_map<string, vector<pair<int, double> > > _invertIndexTable; // 倒排索引表对象





}// end of wd;
