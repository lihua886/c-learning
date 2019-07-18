#include <iostream>
#include <string>
using std::cout;
using std::cin;
using std::endl;
using std::string;


class Base{
public:
     virtual void func(){
        cout<<"base::func()"<<endl;
    }
};
class Child
:public Base{
    void func(){
        cout<<"Child::func()"<<endl;
    }
     virtual void func1(){
        cout<<"Child::func1()"<<endl;
    }
};

int main()
{

    Base*  base=new Child;
    //base->func();
    typedef void(*p)(void);

    p func=(p)*(long*)*(long*)&(*base);  
    func();
    p func1=(p)(((long *)*(long*)*(long*)&(*base))+1);  
    func1();
    return 0;
}

