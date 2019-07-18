#include <pthread.h>
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
        pthread_once(&once,Init);
        return m_pInstance;
    }
    static void Init(){
        if(m_pInstance==nullptr){
            m_pInstance=new Signalton();
            atexit(destory);
        }
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
    static pthread_once_t once;

};
Signalton* Signalton::m_pInstance=nullptr;
//Signalton* Signalton::m_pInstance=getInstance();
pthread_once_t Signalton::once=PTHREAD_ONCE_INIT;
int main()
{
    Signalton*p1 =Signalton::getInstance();
    p1->print();
    //p1->destory();
    return 0;
}

