#pragma once
#include "Warrior.h"


namespace warcraft{
class Lion
:public Warrior
{
public:
    Lion(Color color, size_t id, size_t hp, size_t forces, size_t loyalty)
        : Warrior(color, "lion", id, hp, forces, LION_TYPE) 
        ,_loyalty(loyalty){}
    WarriorPtr getWarriorPtr(){
        return shared_from_this();
    }
#if 0
    virtual size_t getLoyalty() const override 
    { 
        return _loyalty;  
    }
#endif
    ~Lion(){}
private:
    size_t _loyalty;
};
}
