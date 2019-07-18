#pragma once

#define ___TRACE(...) fprintf(stdout, "file[%s]line[%u]func[%s]::",__FILE__,__LINE__,__func__);\
    fprintf(stdout,__VA_ARGS__)
#include "Warrior.h"
#include "type.h"
#include <memory>

namespace warcraft{
using WarriorPtr=std::shared_ptr<warcraft::Warrior>;

class WarriorView
{
public:
    WarriorView(WarriorPtr warrior)
        : _warrior(warrior){}
    void showBorn() const;
    void showMarch() const;
    void showEarnElements() const;
    void showReachDestination() const;
    void showtime() const;
protected:
    void showName() const;
    void showToCity() const;
    void showInCity() const;
    void showElementsAndForces() const;
protected:
    WarriorPtr _warrior;
};
}

