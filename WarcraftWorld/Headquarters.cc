#include "Headquarters.h"
#include "Dragon.h"
#include "Iceman.h"
#include "Lion.h"
#include "Ninja.h"
#include "Wolf.h"
#include <algorithm>


namespace warcraft{
using WarriorPtr=std::shared_ptr<Warrior>;
WarriorPtr Headquarters::create(){
    switch(getNextWarriorType()){
    case DRAGON_TYPE:
        return createDragon(_nextWarriorIndex+1,GameConfig::getInstance()->warriorInitalLife(DRAGON_TYPE),
                    GameConfig::getInstance()->warriorInitalAttack(DRAGON_TYPE) );
    case NINJA_TYPE:
        return createNinja(_nextWarriorIndex+1,GameConfig::getInstance()->warriorInitalLife(NINJA_TYPE),
                    GameConfig::getInstance()->warriorInitalAttack(NINJA_TYPE) );
    case ICEMAN_TYPE:
        return createIceman(_nextWarriorIndex+1,GameConfig::getInstance()->warriorInitalLife(ICEMAN_TYPE),
                    GameConfig::getInstance()->warriorInitalAttack(ICEMAN_TYPE) );
    case LION_TYPE:
        return createLion(_nextWarriorIndex+1,GameConfig::getInstance()->warriorInitalLife(LION_TYPE),
                    GameConfig::getInstance()->warriorInitalAttack(LION_TYPE) );
    case WOLF_TYPE:
        return createWolf(_nextWarriorIndex+1,GameConfig::getInstance()->warriorInitalLife(WOLF_TYPE),
                    GameConfig::getInstance()->warriorInitalAttack(WOLF_TYPE) );
}
}
WarriorPtr Headquarters::createIceman(size_t id, size_t hp, size_t forces){
     if(hp<=getElements()){
         WarriorPtr iceman(new Iceman(getColor(),id,hp,forces));
         setElements(getElements()-hp);
         _warriors.push_back(iceman);
         ++_warriorTypeAmounts[ICEMAN_TYPE];
         ++_nextWarriorIndex;
         return iceman;
     }else{
        return nullptr;
     }
          
}
WarriorPtr Headquarters::createLion(size_t id, size_t hp, size_t forces){
     if(hp<=getElements()){
         WarriorPtr  lion(new Lion(getColor(),id,hp,forces,0));
         setElements(getElements()-hp);
         _warriors.push_back(lion);
         ++_warriorTypeAmounts[LION_TYPE];
         ++_nextWarriorIndex;
         return lion;
     }else{
        return nullptr;
     }
}
WarriorPtr Headquarters::createWolf(size_t id, size_t hp, size_t forces){
     if(hp<=getElements()){
         WarriorPtr wolf(new Wolf(getColor(),id,hp,forces));
         setElements(getElements()-hp);
         _warriors.push_back(wolf);
         ++_warriorTypeAmounts[WOLF_TYPE];
         ++_nextWarriorIndex;
         return wolf;
     }else{
        return nullptr;
     }
}
WarriorPtr Headquarters::createNinja(size_t id, size_t hp, size_t forces){
     if(hp<=getElements()){
         WarriorPtr ninja(new Ninja(getColor(),id,hp,forces));
         setElements(getElements()-hp);
         _warriors.push_back(ninja);
         ++_warriorTypeAmounts[NINJA_TYPE];
         ++_nextWarriorIndex;
         return ninja;
     }else{
        return nullptr;
     }
}
WarriorPtr Headquarters::createDragon(size_t id, size_t hp, size_t forces){
     if(hp<=getElements()){
         WarriorPtr dragon(new Dragon(getColor(),id,hp,forces,0));
         setElements(getElements()-hp);
         _warriors.push_back(dragon);
         ++_warriorTypeAmounts[DRAGON_TYPE];
         ++_nextWarriorIndex;
         return dragon;
     }else{
        return nullptr;
     }
}
    //添加胜利者
void Headquarters::addWinner(WarriorPtr warrior){
   // __TRACE("add winners %s\n",warrior->getName().c_str());
     _winners.push(warrior);
}
    //奖励胜利者
void Headquarters::reward(){
    while(!_winners.empty()&&_elements>=8){
        WarriorPtr w=_winners.top();
    // __TRACE("reward %s!\n",w->getName().c_str());
        _winners.pop();
        w->beRewarded();
        w->sentElementsToHeadquarters();
        _elements -=8;
    }
    while(!_winners.empty()){
        _winners.pop();
    }
}











}











