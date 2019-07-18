#include "Warrior.h"
#include "City.h"
#include "Lion.h"
#include "DragonView.h"
#include "BattleView.h"
#include "CityView.h"
#include "WarriorView.h"
#include "algorithm"

namespace warcraft{
using WarriorPtr=std::shared_ptr<Warrior>;
void City::produceElements(){
    _elements +=10;
}

void City::attach(WarriorPtr warrior){
        if(warrior->getColor()==RED){
            if(find(_redWarriors.begin(),_redWarriors.end(),warrior)==_redWarriors.end())
              _redWarriors.push_back(warrior);
        }else{
            if(find(_blueWarriors.begin(),_blueWarriors.end(),warrior)==_blueWarriors.end())
              _blueWarriors.push_back(warrior);
        }
}
void City::detach(WarriorPtr warrior){
//    __TRACE("erase begin!\n");
    if(warrior->getColor()==RED){
       _redWarriors.erase(remove(_redWarriors.begin(),_redWarriors.end(),warrior),_redWarriors.end());
       // _redWarriors.clear();
    }else{
       _blueWarriors.erase(remove(_blueWarriors.begin(),_blueWarriors.end(),warrior),_blueWarriors.end());
       // _blueWarriors.clear();
    }
//    __TRACE("erase end!\n");
}
void City::startBattle(){
    if(_redWarriors.size()==1&&_blueWarriors.size()==1){
         battle(*_redWarriors.begin(),*_blueWarriors.begin());

    }
}
void City::takenBy(WarriorPtr warrior){
 //   __TRACE("take Element %ld from city\n",_elements);
     warrior->setEarnElements(_elements);
     _elements =0;
}


void City::battle(WarriorPtr warrior1,WarriorPtr warrior2){
    //左边是红魔武士，右边是蓝魔武士
 //   __TRACE("flag= %d,city=%ld\n",_flag,_id);
    if(_flag==BLUE||(_flag==NOTSET&&_id%2==0)){
       warrior1.swap(warrior2);
    }
    size_t LionHp;
    if(warrior2->getType()==LION_TYPE){
         LionHp=warrior2->getHp();
    }
    //   __TRACE("%s= %ld,%s=%ld\n",warrior2->getName().c_str(),warrior2->getHp(),warrior1->getName().c_str(),warrior1->getHp());
    warrior1->attack(warrior2);
    BattleView battleView(warrior1,warrior2);
    battleView.showBattle();
    //   __TRACE("%s= %ld,%s=%ld\n",warrior2->getName().c_str(),warrior2->getHp(),warrior1->getName().c_str(),warrior1->getHp());
    if(warrior2->getHp()==0){
  //      __TRACE("death!\n");
        if(warrior2->getType()==LION_TYPE){
            warrior1->setHp(warrior1->getHp()+LionHp);
        }
        battleView.showDeath(warrior2);
        warrior1->beWinner();
        takenBy(warrior1);
        WarriorView Element(warrior1);
        Element.showEarnElements();
        warrior1->sentElementsToHeadquarters();
        if(isChangingFlag(warrior1)){
   //         __TRACE("flag change!\n");
            CityView flagView(this);
            flagView.showFlag();
        }
    }else{
       if(warrior1->getType()==LION_TYPE){
           LionHp=warrior1->getHp();
       }
    //__TRACE("ack= %ld,den=%ld\n",warrior2->getHp(),warrior1->getHp());
       warrior2->defense(warrior1);
       battleView.showDefense();
    //   __TRACE("%s= %ld,%s=%ld\n",warrior2->getName().c_str(),warrior2->getHp(),warrior1->getName().c_str(),warrior1->getHp());
       if(warrior1->getHp()==0){
            if(warrior1->getType()==LION_TYPE){
                warrior2->setHp(warrior2->getHp()+LionHp);
            }
   //        __TRACE("death!\n");
           battleView.showDeath(warrior1);
           warrior2->beWinner();
           takenBy(warrior2);
           WarriorView Element(warrior2);
           Element.showEarnElements();
           warrior2->sentElementsToHeadquarters();
           if(isChangingFlag(warrior2)){
    //           __TRACE("flag change!\n");
              CityView flagView(this);
              flagView.showFlag();
            }
       }else{
           if(warrior1->getType()==DRAGON_TYPE){
               DragonView drView(warrior1);
               drView.showYell();
           }
   //       __TRACE("ack= %ld,den=%ld\n",warrior2->getHp(),warrior1->getHp());
           //std::cout<<"no warrior death!"<<std::endl;
        //   return false;
       }
    }
}


bool City::isChangingFlag(WarriorPtr warrior){
    if(warrior->getColor()==RED){
        if(_blueWinCount==1){
            _blueWinCount=0;
        }
        _redWinCount++;
    }else{
        if(_redWinCount==1){
            _redWinCount=0;
        }
        _blueWinCount++;
    }
    if(_blueWinCount==2){
        _flag=BLUE;
        _blueWinCount=0;
        return true;
    }else if(_redWinCount==2){
        _flag=RED;
        _redWinCount=0;
        return true;
    }else{
        return false;
    }
}

}
