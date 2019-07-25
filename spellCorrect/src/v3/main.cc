#include "SpellCorrectSever.h"
#include "CacheManger.h"
//#include "TimerThread.h"

int main(){
//    wd::CacheManger::getInstance()->init();
//    wd::TimerThread timer(0,5,std::bind(&wd::CacheManger::periodUpdate,wd::CacheManger::getInstance()));
//    timer.start();


    wd::SpellCorrectSever sever;
    sever.start();
}
