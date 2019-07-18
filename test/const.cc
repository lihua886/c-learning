#include <iostream>
#include <string>
using std::cout;
using std::cin;
using std::endl;
using std::string;


class TextBlock{
public:

    TextBlock(const char*p)
    :text(p){}
    const char& operator[](std::size_t position)  const
    {
        return text[position];
    }
    char& operator[](std::size_t position)
    {
        return text[position];
    }
    void print() const{
        cout<<"const"<<text<<endl;
    }
  //  void print(){
  //      cout<<"non-const"<<text<<endl;
  //  }
private:
    std::string text;
};


int main()
{
    TextBlock tb("hello");
    tb.print();
    const TextBlock ctb("world");  //常量对象 调用常量版本
    ctb.print();
  //  const char & i=ctb[0];//引用必须初始化,
  //  cout<<i<<endl;
//    const char & j=tb[0];//
//    cout<<j<<endl;
//    tb[0]='j';
//    cout<<ctb[0]<<endl;
//    cout<<tb[0]<<endl;
//    cout<<j<<endl;
    return 0;
}

