#include "Configuration.h"
#include "DirScanner.h"
#include "PageLib.h"



int main(){
    wd::Configuration config("/home/fsq/study/c++/c-learning/TinySearchEngine/conf/myconf.conf");
    config.readConfigFile();
    config.readStopWords();
//    config.print();
    wd::DirScanner dirscan(config);
    dirscan();
//    dirscan.print();
    wd::PageLib page(config,dirscan);
    page.create();
    page.store();
}

