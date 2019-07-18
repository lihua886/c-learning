#include "WarriorView.h"
#include "GameTime.h"
using namespace warcraft;
using std::cout;
using std::endl;


void WarriorView::showtime()   const{
    GameTime::getInstance()->showTime();
}

void WarriorView::showBorn() const{
    //__TRACE("warrior show\n");
    if(_warrior){
        showtime();
        showName();
        cout<<" born"<<endl;
    }
}
void WarriorView::showMarch() const{
    //__TRACE("warrior show\n");
    if(_warrior){
        showtime();
        showName();
        cout<<" marched";
        showToCity();
        cout<<" with ";
        showElementsAndForces();
    }
}
void WarriorView::showEarnElements() const{
    if(_warrior){
        showtime();
        showName();
        cout<<" earned "<<_warrior->getEarnElements()<<" elements for his headquarters"<<endl;
    }
}
void WarriorView::showReachDestination() const{ 
    if(_warrior){
        showtime();
        showName();
        cout<<" reached "<<(_warrior->getColor()==RED?"blue":"red")<<" headquarters with ";
        showElementsAndForces();
    }
}
void WarriorView::showName() const{
    cout<<" "<<(_warrior->getColor()==RED?"red":"blue")<<" "<<_warrior->getName()<<" "
            <<_warrior->getId();
}
void WarriorView::showToCity() const{
    cout<<" to city "<<_warrior->getCityId();
}
void WarriorView::showInCity() const{
    cout<<" in city "<<_warrior->getCityId();
}
void WarriorView::showElementsAndForces() const{
    cout<<_warrior->getElements()<<" elements and force "
        <<_warrior->getForces()<<endl;
}
