#include "str-ws.h"
#include <iostream>
#include <string>
#include <cwctype>
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::wstring;
void test01(){
    string s="王道ABC";
    wstring ws=wd::s2Ws(s);

    for(auto & it:ws){
        if(iswalpha(it)){
            it=towlower(it);
        }
    }
    string news=wd::ws2S(ws);
    cout<<news<<endl;
}


int main()
{
    test01();
    return 0;
}

