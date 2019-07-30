#include "DirScanner.h"
#include "Configuration.h"
#include <func.h>
#include <iostream>
using std::cout;
using std::endl;





namespace wd{


void DirScanner::operator()(){
    traverse(_conf.getConfigMMap()["yuliao"]);
}
void DirScanner::traverse(const string &dirpath){
    DIR* dir;
    dir=::opendir(dirpath.c_str());
    struct dirent *p;
    char temppath[1024]={0};
    while((p=readdir(dir))!=NULL)
    {
        if(!strcmp(p->d_name,".")||!strcmp(p->d_name,".."))
            continue;
        sprintf(temppath,"%s/%s",dirpath.c_str(),p->d_name);
        if(4==p->d_type){
            traverse(temppath);
        }else{
            _files.emplace_back(string(temppath));            
        }
    }
    closedir(dir);
}
void DirScanner::print() const{
    for(auto &it:_files){
        cout<<it<<endl;        
    }       

}


}// end of wd
