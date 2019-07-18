#include <iostream>
#include <string>
using std::cout;
using std::cin;
using std::endl;
using std::string;

class A{
public:
    virtual void a(){
        cout<<"A;:a()"<<endl;
    }
    void b(){
        cout<<"A;:b()"<<endl;
    }
    void c(){
        cout<<"A;:c()"<<endl;
    }
    virtual void d(){
        cout<<"A;:d()"<<endl;
    }
private:

};
class B{
public:
    virtual void a(){
        cout<<"B;:a()"<<endl;
    }
    void b(){
        cout<<"B;:b()"<<endl;
    }
    void c(){
        cout<<"B;:c()"<<endl;
    }
private:

};

class C
:public A,public B{
public:
    virtual void a(){
        cout<<"D;:a()"<<endl;
    }
    void d(){
        cout<<"D;:d()"<<endl;
    }
    void c(){
        cout<<"D;:c()"<<endl;
    }
};
int main()
{
    C c;
    A * pa=&c;
    B * pb=&c;
    printf("pa=%p\n",pa);
    printf("pb=%p\n",pb);
 //   pa->a();
 //   //pa->b();
 //   pa->c();
 //   pa->d();
    return 0;
}

