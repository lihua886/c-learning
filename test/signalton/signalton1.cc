#include <iostream>
#include <string>
using std::cout;
using std::cin;
using std::endl;
using std::string;



class Signalton{
    class Autorelease{
    public:
        Autorelease(){}
        ~Autorelease(){
            if(m_pInstance){
                delete m_pInstance;
                m_pInstance=nullptr;
            }
        }
    };
public:
    static Signalton* getInstance(){
        if(m_pInstance==nullptr){
            m_pInstance=new Signalton();
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
    static Autorelease m_auto;
};
Signalton* Signalton::m_pInstance=nullptr;
Signalton::Autorelease Signalton::m_auto;
int main()
{
    Signalton*p1 =Signalton::getInstance();
    p1->print();
    //p1->destory();
    return 0;
}

