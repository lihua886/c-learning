#include <iostream>
#include <string>
#include <limits>
using std::cout;
using std::cin;
using std::endl;
using std::string;


class Person{
public:
    Person(){}
    Person(int a,int b)
    :m_a(a)
    ,m_b(b){}
    Person operator+(const Person & p){
        Person tmp;
        tmp.m_b=m_b+p.m_b;
        tmp.m_a=m_a+p.m_a;
        return tmp;
    } 
     
    friend std::ostream & operator<<(std::ostream & os,const Person &p);
    friend std::istream & operator>>(std::istream & is,Person &p);

    void print() const{
        cout<<"("<<m_a<<","<<m_b<<")";
    }
private:
    int m_a;
    int m_b;
};
std::ostream & operator<<(std::ostream & os,const Person &p){
    os<<"("<<p.m_a<<","<<p.m_b<<")";
    return os;
}

void readDoubleData(std::istream & is,int &p){
    cout<<"Pls input valid data:"<<endl;
    while(is>>p,!is.eof()){
        if(is.bad()){
            cout<<"istream is corrupted"<<endl;
            return;
        }else if(is.fail()){
            is.clear();
            is.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            cout<<"Pls input valid data:"<<endl;
            continue;
        }
        break;
    }
}
std::istream & operator>>(std::istream & is,Person &p){
      readDoubleData(is,p.m_a);
      readDoubleData(is,p.m_b);
      return is;
}
void test01(){
    Person p1(1,2),p2(3,4);
    Person p3=p1+p2;
    p3.print();
    Person p4;
    cin>>p4;
    cout<<p4<<endl;

}
int main()
{
    test01();
    return 0;
}

