#pragma once

#include "Query.h"
#include "AndQuery.h"
#include "NotQuery.h"
#include "OrQuery.h"
#include <cctype>
using namespace std;


struct node{
    string s;
    char op;
    bool flag;
};
stack<node> s;
queue<node> qu;
map<char,int> op;
void setPriority(){
     op['~']=3;
     op['&']=2;
     op['|']=1;
}
class Paser{
public:
    Query dopaser(string & exp){
        return Queryinit(exp);
    }
private:
    bool expChange(string &);
    Query Queryinit(string &);
};
bool Paser::expChange(string &exp){
    node temp;
    setPriority();
    exp.erase(remove_if(exp.begin(),exp.end(),[](const char c){
               return isspace(c);
               }),exp.end());
    for(size_t i=0;i<exp.size();){
        if(isalpha(exp[i])){
            string word;
            while(isalpha(exp[i])){
                word.push_back(exp[i++]);
            }
            temp.flag=true;  //true 代表单词 
            temp.s=word;
            qu.push(temp);
        }else if(exp[i]=='('){
            temp.flag=false;
            temp.op='(';
            s.push(temp);
            i++;
        }else if(exp[i]==')'){
            temp.flag=false;
            temp.op=s.top().op;
            s.pop();
            while(!s.empty()&&temp.op!='('){
                qu.push(temp);
                temp.op=s.top().op;
                s.pop();
            }
            if(temp.op!='('){
                return false;
            }
            ++i;
        }else if(exp[i]=='|'||exp[i]=='&'||exp[i]=='~'){
            temp.flag=false;
            while(!s.empty()&&op[exp[i]]<=op[s.top().op]){
                if(s.top().op=='('){
                    break;
                }
                qu.push(s.top());
                s.pop();
            }
            temp.op=exp[i];
            s.push(temp);
            ++i;
        }else{
            cout<<"invalid char"<<endl;
            return false;
        }
    }
    while(!s.empty()){
        if(s.top().op=='('){
            return false;
        }
        qu.push(s.top());
        s.pop();
    }
    return true;
}
Query Paser::Queryinit(string &exp){
    stack<Query> s;
    if(!expChange(exp)){
        cout<<"表达式有误"<<endl;
        exit(0);
    }else{
        Query query1,query2;
        node cur;
        while(!qu.empty()){
            cur=qu.front();
            qu.pop();
            if(cur.flag){
              //__TRACE("%s\n",cur.s.c_str());
              Query temp(cur.s);
              s.push(temp);
            }else{
              query2=s.top();
              s.pop();
              if(!s.empty()){
                 query1=s.top();
                 s.pop();
              }
             // __TRACE("%c\n",cur.op);
              switch(cur.op){
              case '~':
                  s.push(Query(~(query2)));
                  break;
              case '&':
                  s.push(Query(query1&query2));
                  break;
              case '|':
                  s.push(Query(query1|query2));
                  break;
              }
            }
     }
     }
     Query q=s.top();
     return q;
}







        
