#include <iostream>
#include <string>
#include <regex>
#include <fstream>
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::fstream;
int main()
{
    fstream fs("testfile");
    string content;
    fs>>content;
    cout<<"begin content:"<<endl;
    cout<<content<<endl;
    std::regex reg("<.*?>");
    content=std::regex_replace(content,reg,"");
    cout<<"end content:"<<endl;
    cout<<content<<endl;

    return 0;
}

