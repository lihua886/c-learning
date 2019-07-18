#include "WarcraftWorld.h"
#include "WarriorView.h"
#include "Iceman.h"
#include "City.h"
#include "HeadquarterView.h"
#include <algorithm>


namespace warcraft{
void WarcraftWorld::init(){
     _redHeadquarters=(Headquarters*)new RedHeadquarters(GameConfig::getInstance()->headquartersInitialElements()); 
     _blueHeadquarters=(Headquarters* )new BlueHeadquarters(GameConfig::getInstance()->headquartersInitialElements()); 
     _redHeadquarters->setId(0);
     size_t citys=GameConfig::getInstance()->cityCount();
     _blueHeadquarters->setId(citys+1);
     for(size_t i=0;i<=citys+1;i++){
         _cities.push_back(City(i));
     }
}
void WarcraftWorld::createWarrior(){
    auto redwarrior=_redHeadquarters->create();
    if(redwarrior){
       redwarrior->setHeadquarters(_redHeadquarters);
     //  __TRACE("red %s born\n",redwarrior->getName().c_str());
       WarriorView warView1(redwarrior);
       warView1.showBorn();
    }
    auto bluewarrior=_blueHeadquarters->create();
    if(bluewarrior){
       bluewarrior->setHeadquarters(_blueHeadquarters);
    //   __TRACE("blue %s born\n",bluewarrior->getName().c_str());
       WarriorView warView2(bluewarrior);
       warView2.showBorn();   
    }
}
void WarcraftWorld::March(WarriorPtr warrior){
        size_t cityId=warrior->getCityId();
     //   __TRACE("city.size()=%ld,cityId=%ld,color=%d\n",_cities.size(),warrior->getCityId(),warrior->getColor());
        if((cityId<_cities.size()-1&&warrior->getColor()==RED)
           ||(cityId>0&&warrior->getColor()==BLUE)){
            _cities[cityId].detach(warrior);
             if(warrior->getHp()>0){
                warrior->march();
             }
        }
        if(warrior->getHp()>0){
           cityId=warrior->getCityId();
           _cities[cityId].attach(warrior);
        }
}
void WarcraftWorld::warriorMarch(Headquarters * headquarters){
     auto warriors=headquarters->getWarriors();
     for(auto it=warriors.begin();it!=warriors.end();++it){

      //   __TRACE("%s \n",it->getName().c_str());
         March(*it);
     }
}
void WarcraftWorld::showMarch(){
    for(auto it=_cities.begin();it!=_cities.end();++it){
       auto red=it->getRedWarriors();
       auto blue=it->getBlueWarriors();
       if(!red.empty()){
           WarriorView marchView(red.back());
           if(it==_cities.end()-1){
               marchView.showReachDestination();
           }else{
               marchView.showMarch();
           }
       }
       if(!blue.empty()){
           WarriorView marchView(blue.back());
           if(it==_cities.begin()){
               marchView.showReachDestination();
           }else{
               marchView.showMarch();
           }
       }
    }
}
bool WarcraftWorld::warriorMarch(){
     warriorMarch(_redHeadquarters);
       //  displayWarrior();
     warriorMarch(_blueHeadquarters);
     //    displayWarrior();
     //  __TRACE("red=%ld,blue=%ld\n",_cities[0].getWarriorAmount(),_cities[_cities.size()-1].getWarriorAmount());
       if(_cities[0].getWarriorAmount()==2||_cities[_cities.size()-1].getWarriorAmount()==2)
            return false;
    return true;
}

bool WarcraftWorld::checkRedHeadquartersBeTaken(){
     return _cities[0].getWarriorAmount()==2;
}
bool WarcraftWorld::checkBlueHeadquartersBeTaken(){
     return _cities[_cities.size()-1].getWarriorAmount()==2;
}

void WarcraftWorld::cityProduceElements(){
    for(auto it=_cities.begin()+1;it!=_cities.end()-1;++it){
         it->produceElements(); 
    }
}

void WarcraftWorld::takeCityElements(){
    for(auto it=_cities.begin()+1;it!=_cities.end()-1;++it){
        //__TRACE("start!\n");
        if(it->getWarriorAmount()==1){
            auto red=it->getRedWarriors();
            auto blue=it->getBlueWarriors();
            if(!red.empty()){
                it->takenBy(red.front());
                WarriorView showEarn(red.front());
                showEarn.showEarnElements();
                red.front()->sentElementsToHeadquarters();
                _redHeadquarters->addElements();
            }else{
                it->takenBy(blue.front());
                WarriorView showEarn(blue.front());
                showEarn.showEarnElements();
                blue.front()->sentElementsToHeadquarters();
                _blueHeadquarters->addElements();
            }
        } 
    }

}

void WarcraftWorld::battle(){
     auto it=_cities.begin();
     for(;it!=_cities.end()-1;it++){
        it->startBattle();
     }
     _redHeadquarters->reward();
     _blueHeadquarters->reward();
     _redHeadquarters->addElements();
     _blueHeadquarters->addElements(); 
}

void WarcraftWorld::headquartersReportElements(){
    HeadquartersView headViews(_redHeadquarters);
    headViews.showLeftElements();
    HeadquartersView headViews1(_blueHeadquarters);
    headViews1.showLeftElements();
}


}

