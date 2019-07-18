#pragma once

#include "Warrior.h"

namespace warcraft{
class Iceman
: public Warrior{
public:
    Iceman(Color color, size_t id, size_t hp, size_t forces)
        : Warrior(color, "iceman", id, hp, forces, ICEMAN_TYPE), 
        _steps(0){}
    //iceman 每前进两步，在第2步完成的时候，生命值会减少9，
    //攻击力会增加20。//但是若生命值减9后会小于等于0，
    //则生命值不减9,而是变为1。即iceman不会因走多了而死。
     void march() override{
      //  __TRACE("333 iceman  march \n");
        //if(_color==BLUE && _cityId>0){
        if(_color==BLUE){
           --_cityId;
        //}else if(_color==RED && _cityId < cityCount){
        }else if(_color==RED){
           ++_cityId;
        }
#if 1
        if(++_steps==2){
            _hp=_hp>9?(_hp-9):1; 
            _forces += 20;
          _steps=0;
        } 
#endif
     }
    ~Iceman(){}
private:
    size_t _steps;//前进的步数
};
}

