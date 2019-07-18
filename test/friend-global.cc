#include <iostream>
#include <string>
using std::cout;
using std::cin;
using std::endl;
using std::string;


class Building{
public:
    friend void goodfriend(const Building *p);
    Building(){
        settingRoom="客厅";
        bedRoom="卧室";
    }
    string settingRoom;
private:
    string bedRoom;
};

//全局函数
void goodfriend(const Building *p){
    cout<<"I visit "<<p->settingRoom<<endl;
    cout<<"I visit "<<p->bedRoom<<endl;
}
void test01(){
    Building * p=new Building;
    goodfriend(p);
}
int main()
{ 
    test01();
    return 0;
}

