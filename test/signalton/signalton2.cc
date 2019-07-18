#include <stdlib.h>
#include <iostream>
#include <string>
using std::cout;
using std::cin;
using std::endl;
using std::string;



class Signalton{
public:
    static Signalton* getInstance(){
        if(m_pInstance==nullptr){
            m_pInstance=new Signalton();
            atexit(destory);
        }
        return m_pInstance;
    }
    void print() const
    {
        cout<<"print()"<<endl;
    }
    static void destory(){
        if(m_pInstance){
            delete m_pInstance;
            m_pInstance = nullptr;
        }
    }
private:
    Signalton(){
        cout<<"Signalton()"<<endl;
    }
    ~Signalton(){
        cout<<"~Signalton()"<<endl;
    }
private:
    static Signalton * m_pInstance;
};
//Signalton* Signalton::m_pInstance=nullptr;
Signalton* Signalton::m_pInstance=getInstance();
int main()
{
    Signalton*p1 =Signalton::getInstance();
    p1->print();
    //p1->destory();
    return 0;
}

