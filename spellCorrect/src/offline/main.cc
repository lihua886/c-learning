#include "DictProducer.h"
#include "IndexProducer.h"




int main(){
    wd::DictProducer dict("data/enyuliao");
    dict.build_dict();
    dict.store_dict("../../data/en/mydict.dat");
    wd::IndexProducer Index(&dict);
    Index.build_index();
    Index.store_index("../../data/en/index.dat");
    //dict.show_files();
    //dict.show_dict();
}
