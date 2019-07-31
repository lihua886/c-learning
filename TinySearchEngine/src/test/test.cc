#include "DirScanner.h"
#include "Configuration.h"
#include "WordSegmentation.h"
#if 0
void test02(){
    wd::Configuration config("/home/fsq/study/c++/c-learning/TinySearchEngine/conf/myconf.conf");
    config.readConfigFile();
    config.readStopWords();
//    config.print();
    wd::DirScanner dirscan(config);
    dirscan();
    dirscan.print();
}
#endif
void test01(){
    wd::WordSegmentation jieba;
    string s="hello他来到了网易wangyi杭研大厦123 \
                    小明xiaoming和小胡一起去apple离家最近的学校； \
                    英雄联盟lol是最好玩的游戏。";
    vector<string> words=jieba.cut(s);
    for(auto &it:words){
        std::cout<<it<<" ";
    }
    std::cout<<std::endl;
}
int main(){
    test01();
}
