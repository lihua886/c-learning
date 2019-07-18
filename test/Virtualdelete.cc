#include <string.h>
#include <iostream>
#include <string>
using std::cout;
using std::cin;
using std::endl;
using std::string;

class Base{
public:
    Base(const char *base)
    :_base(new char[strlen(base)+1]())
    {
        strcpy(_base,base);
        cout<<"Base(const char *)"<<endl;
    }
    virtual void display(){
        cout<<"Base::display()"<<_base<<endl;
    }
    virtual  ~Base(){ 
        delete []_base;
        cout<<"~Base()"<<endl;
    }
private:
    char *_base;
};

class Derived
:public Base{
public:
     Derived(const char *base,const char *derived)
     :Base(base)
     ,_derived(new char[strlen(derived)+1]())
     {
        cout<<"Derived(const char *,const char *)"<<endl;
     }
     void display(){
         cout<<"Derived::display "<<_derived<<endl;
     }
     
     ~Derived(){
         delete [] _derived;
         cout<<"~Derived()"<<endl;
     }
private:
    char *_derived;
};

int main()
{
    Base * pBase=new Derived("hello","world");
    pBase->display();
    delete pBase;
    return 0;
}

