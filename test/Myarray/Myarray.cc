#include "Myarray.h"
#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

namespace fsq{
Myarray::Myarray()
    :m_Capacity(0)
     ,m_size(0)
     ,m_addrs(new int[1]()){}

Myarray::Myarray(int capacity)
    :m_Capacity(capacity)
    ,m_size(0)
     ,m_addrs(new int[m_Capacity]()){
         cout<<"有参调用"<<endl;
     }
Myarray::Myarray(const Myarray& array)
    :m_Capacity(array.m_Capacity)
    ,m_size(array.m_size)
     ,m_addrs(new int[m_Capacity]()){
         cout<<"拷贝构造"<<endl;
     }
void Myarray::pushBack(int number){
    m_addrs[m_size]=number;
    m_size++;
}
int Myarray::getData(int index){
    return m_addrs[index];
}

void Myarray::setData(int index,int val){
    m_addrs[index]=val;
}

Myarray::~Myarray(){
    delete []  m_addrs;
    m_addrs=nullptr;
    cout<<"析构函数"<<endl;
}
int & Myarray::operator[](int index){
    if(index>=0&&index<m_size){
       return m_addrs[index];
    }
    else{
       cout<<"越界"<<endl;
       exit(-1);
    }

}

}
