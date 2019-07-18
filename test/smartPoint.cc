#include <iostream>
#include <string>
using std::cout;
using std::cin;
using std::endl;
using std::string;


class Person{
public:
    Person(int age)
    :m_age(age)
    {}
    void showAge() const{
        cout<<" age = "<<m_age<<endl;
    }
    ~Person(){
        cout<<"~Person()"<<endl;
    }
private:
    int m_age;
};
class SmartPointer{
public: 
    SmartPointer(Person *p)
    :person(p)
    {}
    Person* operator->(){
        return person;
    }
    Person& operator*(){
        return *person;
    }
    ~SmartPointer(){
        if(person){
            delete  person;
            person=nullptr;
        }
        cout<<"~SmartPointer()"<<endl;
    }
private:
    Person * person;
};

void test01(){
    SmartPointer p1(new Person(10));
    p1->showAge();
    (*p1).showAge();
}


int main()
{
    test01();
    return 0;
}

