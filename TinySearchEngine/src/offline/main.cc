#include "Configuration.h"
#include "DirScanner.h"
#include "PageLib.h"
#include "PageLibPreprocessor.h"
#include "WordSegmentation.h"


int main(){
    wd::Configuration config("/home/fsq/study/c++/c-learning/TinySearchEngine/conf/myconf.conf");
    config.readConfigFile();
    config.readStopWords();
//    config.print();
//    wd::DirScanner dirscan(config);
//    dirscan();
//    dirscan.print();
//    wd::PageLib page(config,dirscan);
//    page.create();
//    page.store();
    wd::WordSegmentation jieba;
    wd::PageLibPreprocessor  pagePre(config,jieba);
    pagePre.readInfoFromFile();
    pagePre.doProcess();
    pagePre.cutRedundantPages();
    pagePre.buildInvertIndexTable();
    pagePre.storeOnDisk();
}

