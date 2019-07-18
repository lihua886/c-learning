#pragma once

#include "Warrior.h"
namespace warcraft{
class Ninja
: public Warrior{
public:
    Ninja(Color color, size_t id, size_t hp, size_t forces)
             : Warrior(color, "ninja", id, hp, forces, NINJA_TYPE){}
    //ninja 挨打了也从不反击敌人，需覆盖virtual 
    virtual void defense(WarriorPtr warrior) override{}
    

    ~Ninja() {}
};
}

