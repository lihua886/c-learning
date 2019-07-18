#include <iostream>
#include <string>
using std::cout;
using std::cin;
using std::endl;
using std::string;


class Building{
    friend class goodFriend;
public:
    Building(){
        settingRoom="客厅";
        bedRoom="卧室";
    }
    string settingRoom;
private:
    string bedRoom;
};
class goodFriend{
public:
    goodFriend(){
        m_ptr=new Building;
    }
    void visit() const{
        cout<<"I visit "<<m_ptr->settingRoom<<endl;
        cout<<"I visit "<<m_ptr->bedRoom<<endl;
    }
private:
    Building *m_ptr;
};

void test01(){
    goodFriend guy;
    guy.visit();
}
int main()
{ 
    test01();
    return 0;
}

