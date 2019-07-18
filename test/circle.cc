#include <iostream>
using namespace std;

//求圆的周长的类
const double pi=3.14;
class Circle{
public:

    double getcircle(){
        return 2*pi*radius;
    }

    void setfadius(double r){
        radius=r;
    }
    double radius;
};

int main()
{
    Circle c1;
    c1.setfadius(1.0);
    cout<<"圆的周长为："<<c1.getcircle()<<endl;
}

