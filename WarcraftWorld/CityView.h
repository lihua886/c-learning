#pragma once

#include "GameTime.h"
#include "City.h"
#include "type.h"
namespace warcraft{
class CityView{
public:
    CityView(City * city) 
        : _city(city) {}
    //城市更换旗子时
    void showFlag() const{
       GameTime::getInstance()->showTime();
       std::cout<<" "<<(_city->getFlag()==RED?"red":"blue")<<" flag raised "
                <<"in city "<<_city->getId()<<std::endl;   
    }
private:
    City * _city;
};
}

