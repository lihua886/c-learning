#include <stdio.h>
#include <string.h>
#include <iostream>
#include <string>
using std::cout;
using std::cin;
using std::endl;
using std::string;

class String{
public:
    String(){
        m_pstr=NULL;
    }
    String(const char *pstr)
        :m_pstr(new char[strlen(pstr)+1]())
    {
        strcpy(m_pstr,pstr);
    }
    String(const String &rhs)
        :m_pstr(new char[strlen(rhs.m_pstr)+1]())
    {
        strcpy(m_pstr,rhs.m_pstr);
    }
    String & operator=(const String & rhs){
//        if(this!=&rhs){
//            delete [] m_pstr;
//            m_pstr=new char[strlen(rhs.m_pstr)+1]();
//            strcpy(m_pstr,rhs.m_pstr);
//        } 
            if(this!=&rhs){
                String tempStr(rhs);
                char *temp=tempStr.m_pstr;
                tempStr.m_pstr=m_pstr;
                m_pstr=temp;// 实例交换
            }
        return *this;
    }
    void print(){
        size_t i;
        if(m_pstr!=NULL){
            for(i=0;i<strlen(m_pstr);i++){
                printf("%c",m_pstr[i]);
            }
        }
        printf("\n");
    }
    ~String(){
        if(m_pstr!=nullptr){
            delete [] m_pstr;
            m_pstr=NULL;
        }
    }
private:
    char* m_pstr;
};

int main(void)
{
    String str1;
    str1.print();

    String str2 = "Hello,world";
    String str3("wangdao");

    str2.print();       
    str3.print();   

    String str4 = str3;
    str4.print();

    str4 = str2;
    str4.print();
    cout<<"1+1 = "<<1+1<<endl;
    return 0;

}
