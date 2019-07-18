#include <iostream>
#include <string>
#include <exception>
#include <stdexcept>
using std::cout;
using std::cin;
using std::endl;
using std::string;

#if 1
class Exception
:public std::exception{
public:
    const char * what() const throw(){
        return "Exception::error!";
    }
};
#endif
class Person{
public:
    string _name;
    int _age;
    Person(string name,int age)
        :_name(name),_age(age)
    {
        if(_age>100||_age<0){
            throw  Exception();
            //   throw std::out_of_range("out of range!");
        }

    }
};

int main()
{
    try{
    Person("jack",200);
    }
    catch(std::exception & e){
        cout<<e.what()<<endl;
    }
    return 0;
}

