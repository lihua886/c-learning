#include "SpellCorrectSever.h"
#include "CacheManger.h"

int main(){
    wd::CacheManger::init();
    wd::SpellCorrectSever sever;
    sever.start();
}
