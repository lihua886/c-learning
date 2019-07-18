#include <iostream>
#include <string>
using std::cout;
using std::cin;
using std::endl;
using std::string;

int main()
{
    int  a=10;
    float b=*(float*)&a;
    float c=a;
    cout<<"sizeof(a)= "<<sizeof(a)<<" a= "<<a<<endl
        <<"sizeof(b)= "<<sizeof(b)<<" b= "<<b<<endl
        <<"c= "<<c<<endl;
    return 0;
}

