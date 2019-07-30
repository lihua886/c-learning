#include "tinyxml2.h"
#include "PageLib.h"    
#include "Configuration.h"
#include "DirScanner.h"
#include "str-ws.h"
#include <fstream>
#include <iostream>
#include <regex>
using std::make_pair;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using tinyxml2::XMLDocument;
using tinyxml2::XMLElement;

#define __TRACE(...) fprintf(stdout, "file[%s]line[%u]func[%s]::",__FILE__,__LINE__,__func__);\
    fprintf(stdout,__VA_ARGS__)


namespace  wd{

void PageLib::create(){
    long docid=1;
    for(auto &it:_dirScanner.getFiles()){
        XMLDocument doc;
        doc.LoadFile(it.c_str());
        XMLElement* rss=doc.RootElement();
        XMLElement* channel=rss->FirstChildElement("channel");
        XMLElement* item=channel->FirstChildElement("item");
        while(item){
            RssItem TmpItem;
            cout<<"title"<<endl;
            XMLElement * title=item->FirstChildElement("title");
            if(title->GetText()!=NULL){
                TmpItem.title=title->GetText();
            }else{
                item=item->NextSiblingElement();
                continue;
            }
            cout<<TmpItem.title<<endl;
            XMLElement * link=item->FirstChildElement("link");
            TmpItem.link=link->GetText();
            cout<<TmpItem.link<<endl;
            XMLElement * description=item->FirstChildElement("description");
            if(description!=nullptr){
                TmpItem.description=description->GetText();
            }
            XMLElement * content=item->FirstChildElement("content:encoded");
            if(content!=nullptr){
                TmpItem.content=content->GetText();
            }
            item=item->NextSiblingElement();
            RssItemFunc(TmpItem,docid++);
        }
    } 
}//  创建网页库

void PageLib:: RssItemFunc(const RssItem & item,long index){
        std::regex reg("(<[^>]*>)|(&nbsp;)");
       // std::regex reg("<p>&nbsp;</p>");
        std::regex reg1("&gt;");
        std::regex reg2("&lt;");
        string content=std::regex_replace(item.content,reg,"");
        content=std::regex_replace(content,reg1,">");
        content=std::regex_replace(content,reg2,"<");
        string description=std::regex_replace(item.description,reg,"");
        string tmp;
        char buf[100]={0};
        sprintf(buf,"%s%ld%s","<docid>",index,"<docid>");
        tmp.append("<doc>\n")
            .append("    ").append(buf).append("\n")
            .append("    ").append("<url>").append(item.link).append("</url>\n")
            .append("    ").append("<title>").append(item.title).append("</title>\n")\
            .append("    ").append("<content>");
        if(item.content.size()){
            tmp.append(content);
        }else{
            tmp.append(description);
        }
        tmp.append("</content>\n").append("</doc>\n");
       _vecFilesfiles.emplace_back(tmp); 
}
void PageLib::store()
{
    map<string,string> &tmpmap=_conf.getConfigMap();
    ofstream web_ofs(tmpmap["webpagelib"]);
    ofstream offset_ofs(tmpmap["offsetlib"]);
    long k=0;
    for(auto &it:_vecFilesfiles){
        long beginsit=web_ofs.tellp();
        web_ofs<<it;
        _offsetLib[++k]=make_pair(beginsit,it.size());
        offset_ofs<<k<<" "<<beginsit<<" "<<it.size()<<endl;
    }
    web_ofs.close();
    offset_ofs.close();
}//  存储网页库和位置偏移库











}//end of wd    
