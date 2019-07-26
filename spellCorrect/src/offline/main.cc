#include "DictProducer.h"

#include "IndexProducer.h"
#include "SplitTool.h"







int main(){
    wd::DictProducer endict("data/enyuliao");
    endict.build_dict();
    endict.store_dict("../../data/en/mydict.dat");
    wd::SplitTool splitTool;
    wd::DictProducer cndict("data/cnyuliao/art",&splitTool);
    cndict.build_cn_dict();
    cndict.store_dict("../../data/en/mydict.dat");
    
    
    wd::IndexProducer Index;
    Index.build_cnindex();
    Index.store_index("../../data/en/index.dat");
}
