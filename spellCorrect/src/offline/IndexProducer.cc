#include "IndexProducer.h"
#include <fstream>
#include <sstream>
using std::ofstream;
using std::ostringstream;
namespace  wd{

void IndexProducer::build_index(){
    int k=1;
    for(auto &it:*_dict){
        for(auto & i:it.first){
            std::ostringstream oss;
            oss<<i;
            _index[oss.str()].insert(k);
        }
        ++k;
    }
}
void build_cnindex(){

}
void IndexProducer::store_index(const char* path){
    ofstream ofs(path);
    for(auto &it:_index){
        ofs<<it.first<<" ";
        for(auto &it1:it.second){
            ofs<<it1<<" ";
        }
        ofs<<std::endl;
    }
}




}// end of wd

