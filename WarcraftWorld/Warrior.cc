
#include "Warrior.h"
#include "Headquarters.h"


namespace warcraft{
void  Warrior::beWinner(){
    _headquarters->addWinner(shared_from_this());
}//成为胜利者   添加到司令部队列中去
void Warrior::beRewarded(){
      _hp +=8;    
}//被奖励
void Warrior::setEarnElements(size_t element){
    _earnElements=element;
    //__TRACE("earn=%ld\n",_earnElements);
}
void Warrior::sentElementsToHeadquarters(){
     _headquarters->increaseElements(_earnElements);
   // __TRACE("earn=%ld,head earn=%ld\n",_earnElements,_headquarters->getEarnElements());
     _earnElements=0;
}//为司令部获取生命元
}
