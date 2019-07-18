#pragma once
#include "type.h"
#include "GameConfig.h"
#include "GameTime.h"
#include <memory>


namespace warcraft{

class Headquarters;
class Warrior
: public std::enable_shared_from_this<Warrior>
{
public:
   using WarriorPtr=std::shared_ptr<Warrior>;
    Warrior(Color color,
            std::string name,
            size_t id,
            size_t hp,
            size_t forces,
            WarriorType type)
    :_color(color)
    ,_name(name)
    ,_id(id)
    ,_hp(hp)
    ,_forces(forces)
     ,_type(type){
         if(_color==RED){
             _cityId=0;
         }else{
             _cityId=GameConfig::getInstance()->cityCount()+1;
         }
     }
    ~Warrior() {}
    virtual void march(){
    //    __TRACE("111 Warrior::march()\n");
        if(_color==BLUE){
           --_cityId;
        }else if(_color==RED){
           ++_cityId;
        }
    }//行军
    virtual void attack(WarriorPtr warrior){
      warrior->_hp = warrior->_hp>_forces?warrior->_hp-_forces:0;
    }//攻击另一个武士
    virtual void defense(WarriorPtr warrior){
      warrior->_hp = warrior->_hp>_forces/2?warrior->_hp-_forces/2:0;
       // warrior->_hp -= (_forces/2);
    }//反击另一个武士
    void  beWinner();//成为胜利者
    void beRewarded();//被奖励
    void setHeadquarters(Headquarters *head){ _headquarters=head; }
    void setEarnElements(size_t);
    void sentElementsToHeadquarters();//为司令部获取生命元
    Color getColor() const { return _color;  }
    std::string getName() { return _name;  }
    size_t getId() const { return _id;  }
    size_t getHp() const { return _hp;  }
    void   setHp(size_t hp){ _hp=hp; }  
    size_t getCityId() const { return _cityId;  }
    void   setDeath(size_t death)  { _cityId=death;    }
    size_t getElements() const { return _hp;  }
    size_t getEarnElements() const { return _earnElements;  }
    size_t getForces() const { return _forces;  }
    WarriorType getType() const { return _type;  }
protected:
    Color _color;
    std::string _name;
    size_t _id;//编号
    size_t _hp;//生命值
    size_t _forces;//攻击力
    size_t _cityId;//位于某个城市
    size_t _earnElements;//从某个城市中获取的生命元
    WarriorType _type;
    Headquarters * _headquarters;
};
}

