#pragma once

#include "Headquarters.h"

namespace  warcraft{
class HeadquartersView{
public:
    HeadquartersView(Headquarters * headquarters)
        : _headquarters(headquarters){}
    //司令部报告情况时
    void showLeftElements() const{
        GameTime::getInstance()->showTime();
        std::cout<<" "<<_headquarters->getElements()<<" elements "
                <<"in "<<(_headquarters->getColor()==RED?"red":"blue")<<" headquarter "<<std::endl;
    }
    //司令部被占领时
    void showBeTaken() const{
        GameTime::getInstance()->showTime();
        std::cout<<" "<<(_headquarters->getColor()==RED?"red":"blue")<<" headquarter was taken"<<std::endl;
    }
private:
    Headquarters * _headquarters;
};
}
