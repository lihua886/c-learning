#pragma once

#include "Warrior.h"
#include "GameTime.h"
#include <memory>
namespace warcraft{
using WarriorPtr=std::shared_ptr<Warrior>;
class BattleView
{
public:
    BattleView(WarriorPtr warrior1, WarriorPtr warrior2)
        : _warrior1(warrior1)
          , _warrior2(warrior2)
    {}

    void showName(WarriorPtr _warrior) const{
        std::cout<<" "<<(_warrior->getColor()==RED?"red":"blue")<<" "<<_warrior->getName()<<" "
                <<_warrior->getId();
    }
    void showToCity() const{
       std::cout<<" to city "<<_warrior1->getCityId();
    }
    void showInCity() const{
       std::cout<<" in city "<<_warrior1->getCityId();
    }
    void showElementsAndForces(WarriorPtr _warrior) const{
        std::cout<<_warrior->getElements()<<" elements and force "
            <<_warrior->getForces()<<std::endl;
    }
    //武士主动攻击时
    void showBattle() const{
        GameTime::getInstance()->showTime();
        showName(_warrior1);
        std::cout<<" attacked";
        showName(_warrior2);
        showInCity();
        std::cout<<" with ";
        showElementsAndForces(_warrior1);
    }
    ////武士反击时
    void showDefense() const{
        GameTime::getInstance()->showTime();
        showName(_warrior2);
        std::cout<<" fought back against";
        showName(_warrior1);
        showInCity();
        std::cout<<std::endl;
    }
    void showDeath(WarriorPtr warrior) const{
        GameTime::getInstance()->showTime();
        showName(warrior);
        std::cout<<" was killed";
        showInCity();
        std::cout<<std::endl;
    }
private:
    WarriorPtr _warrior1;
    WarriorPtr _warrior2;
    
};
}
