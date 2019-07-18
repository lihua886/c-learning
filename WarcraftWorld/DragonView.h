#pragma once

#include "WarriorView.h"


namespace warcraft{
class DragonView
:public WarriorView{
public:
    DragonView(WarriorPtr warrior)
        : WarriorView(warrior){}
    //dragon 在一次在它主动进攻的战斗结束后，如果还没有战死，就会欢呼
    void showYell() const{
        showtime();
        showName();
        std::cout<<" yelled ";
        showInCity();
    }
};
}

