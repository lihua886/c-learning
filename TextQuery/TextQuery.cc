#include "TextQuery.h"
#include <sstream>
#include <cctype>
#include <algorithm>
#define __TRACE(...) fprintf(stdout, "file[%s]line[%u]func[%s]::",__FILE__,__LINE__,__func__);\
            fprintf(stdout,__VA_ARGS__)


void wordfunc(string & s){
    for(auto &it:s){
        it=tolower(it);
    }
}
// 构造函数
TextQuery::TextQuery(ifstream & is)
    :file(new vector<string>){
        string text;
        while(getline(is,text)){
            file->push_back(text);
            int n=file->size()-1;
            replace_if(text.begin(),text.end(),[](const char c){
                       return ispunct(c);
                       },' ');
            istringstream line(text);
            string word;
            while(line>>word){
                wordfunc(word);
                auto &lines=wm[word];
                if(!lines){
                    lines.reset(new set<line_no>);
                }
                lines->insert(n);
            }
        }
   //     auto loc=wm.find("hair");
   //     cout<<loc->second->size()<<endl;
    }
QueryResult TextQuery::query(const string & word) const{
    //如果没找到，返回一个指向set的指针
    //__TRACE("s=%s\n",word.c_str());
    static shared_ptr<set<line_no>> nodata(new set<line_no>);
    string findWord=word;
    wordfunc(findWord);
    auto loc=wm.find(findWord);

    if(loc==wm.end()){
    //__TRACE("s=%s\n",word.c_str());
        return QueryResult(word,nodata,file);
    }else{
    //__TRACE("s=%s\n",word.c_str());
        return QueryResult(word,loc->second,file);
    }
}
