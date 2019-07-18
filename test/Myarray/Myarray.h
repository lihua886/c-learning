#pragma once


namespace fsq{
class Myarray
{
public:
    Myarray();
    Myarray(int capacity=100);
    Myarray(const Myarray &array);
    ~Myarray();
    void pushBack(int );
    int getData(int );
    void setData(int ,int );
    int & operator[](int );
private:
   int m_Capacity;
   int m_size;
   int *m_addrs;
};
}

