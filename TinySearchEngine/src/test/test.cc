#include "DirScanner.h"
#include "Configuration.h"


void test02(){
    wd::Configuration config("/home/fsq/study/c++/c-learning/TinySearchEngine/conf/myconf.conf");
    config.readConfigFile();
    config.readStopWords();
//    config.print();
    wd::DirScanner dirscan(config);
    dirscan();
    dirscan.print();
}

int main(){
    test02();
}
