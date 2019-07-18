#include <iostream>
#include<string>
using namespace std;

class student{
public:
    void set_name(string name){
       stu_name=name;
    }
    void set_id(int id){
        stu_id=id;
    }
    void print(){
        cout<<"姓名："<<stu_name<<"学号："<<stu_id<<endl;
    }
    int stu_id;
    string stu_name;
};
int main()
{  
    student st;
    st.set_name("小明");
    st.set_id(2);
    st.print();
    return 0;
}

