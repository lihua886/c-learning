#include <iostream>
#include <string>
#include <exception>
using std::cout;
using std::cin;
using std::endl;
using std::string;



class Myexception{
public:
    void printError(){
        cout<<"Myexception::error"<<endl;
    }
};
int operateDev(double a,double b){
    if(b==0){
        //throw  3.14;
        throw Myexception();
    }
    return a/b;
}

void  test(){
    int a=10;
    int b=0;
    try{
    operateDev(a,b);
    }
    catch(Myexception m){
        m.printError();
    }
    catch(...){
        cout<<"test::catch  other exception!"<<endl;
    }
}


int main()
{
    try{
    test();
    }
    catch(double){
        cout<<"test::catch double exception!"<<endl;
    }
    return 0;
}

