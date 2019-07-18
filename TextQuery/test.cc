#include "QueryResult.h"
#include "TextQuery.h"
#include "AndQuery.h"
#include "BinaryQuery.h"
#include "NotQuery.h"
#include "OrQuery.h"
#include "Query.h"
#include "Query_base.h"
#include "Paser.h"
#include <sstream>
using namespace std;

void test01(){
    ifstream ifs("test.txt"); 
    TextQuery q(ifs);
    while(true){
        cout<<"enter word to look for,or q to quit:";
        string s;
        if(!(cin>>s)||s=="q") break;
        print(cout,q.query(s));
    }
}

void test02(){
     ifstream ifs("test.txt"); 
     TextQuery t(ifs);
     Paser paser;
     while(1){
       string s;
       while(getline(cin,s)){ 
           //cout<<s<<endl;
           Query q=paser.dopaser(s);
           print(cout,q.eval(t));
       }
    }
}


int main()
{
   // test01();
    test02();
    return 0;
}

