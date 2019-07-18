#include <iostream>
#include <string>
using std::cout;
using std::cin;
using std::endl;
using std::string;



class Person{
public:

    int m_age;
    static void func(){
        cout<<"我是func函数"<<endl;
    }
    static int m_name;
};
int Person::m_name=0;//类内声明，类外初始化
int main()
{
    Person p1;
    p1.m_name=10;
    Person p2;
    p2.m_name=20;
    cout<<"p1.name="<<p1.m_name<<endl;
    cout<<"p2.name="<<p2.m_name<<endl;

    cout<<" "<<Person::m_name<<endl;
    return 0;
}

