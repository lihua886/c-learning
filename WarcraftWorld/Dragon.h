#pragma once
#include "Warrior.h"

namespace warcraft{
class Dragon
: public Warrior
{
public:
    Dragon(Color color, size_t id, size_t hp, size_t forces, float morale)
        : Warrior(color, "dragon", id, hp, forces,DRAGON_TYPE), 
        _morale(morale){}
    virtual float getMorale() const { return _morale;  }
    WarriorPtr getWarriorPtr(){
        return shared_from_this();
    }
    ~Dragon() {}
private:
    float _morale;
};
}
