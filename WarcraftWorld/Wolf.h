#pragma  once
#include "Warrior.h"


namespace warcraft{
class Wolf
:public Warrior
{
public:
    Wolf(Color color, size_t id, size_t hp, size_t forces)
        : Warrior(color, "wolf", id, hp, forces, WOLF_TYPE),
        _killTimes(0){}
    WarriorPtr getWarriorPtr(){
        return shared_from_this();
    }
    virtual void attack(WarriorPtr warrior) override{
        size_t  rivalHp=warrior->getHp();
        rivalHp =rivalHp>_forces?rivalHp-_forces:0;
        warrior->setHp(rivalHp);
        if(warrior->getHp()==0){
            ++_killTimes;
        }
        if(!_killTimes%2){
            _forces *=2;
            _hp *=2;
        }
    }
private:
    int _killTimes;//击杀次数
};
}

