#include "Myarray.h"
#include <iostream>
#include <string>
using std::cout;
using std::cin;
using std::endl;
using std::string;

void test01(){
    
    fsq::Myarray  *array=new fsq::Myarray(30);
    fsq::Myarray array2(*array);
    
    delete array;
    for(int i=0;i<10;i++){
        array2.pushBack(i);
    }
    for(int i=0;i<10;i++){
        cout<<array2[i]<<" ";
    }
}



int main()
{
    test01();
    return 0;
}

