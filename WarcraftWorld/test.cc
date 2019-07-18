#include "WarcraftWorld.h"
#include "Headquarters.h"
#include "WarriorView.h"
#include "Warrior.h"
using namespace warcraft;
std::vector<WarriorType> types1{DRAGON_TYPE,
                                 NINJA_TYPE,
                                 ICEMAN_TYPE,
                                 LION_TYPE,
                                 WOLF_TYPE};

std::vector<WarriorType> types2 = {
    ICEMAN_TYPE,
    LION_TYPE,
    WOLF_TYPE,
    NINJA_TYPE,
    DRAGON_TYPE,};
//Blue
std::vector<WarriorType> types3 = {
    LION_TYPE,
    DRAGON_TYPE,
    NINJA_TYPE,
    ICEMAN_TYPE,
    WOLF_TYPE
};


void test01(/*const char* filename*/)
{
    GameConfig::getInstance()->setWarriorOrder(types1.begin(),
                                               types1.end());
    GameConfig::getInstance()->readFromFile("warcraft.conf");
    size_t groups=GameConfig::getInstance()->groups();
    for(size_t index=0;index<groups;index++){
        std::cout<<"Case:"<<index+1<<std::endl;
        WarcraftWorld  wow;
        wow.setRedWarriorCreatingOrder(types2.begin(),types2.end());
        wow.setBlueWarriorCreatingOrder(types3.begin(),types3.end());
        wow.start();
        GameConfig::getInstance()->nextGroupId();
        GameTime::getInstance()->reset();
    }
}


int main(int arcv,char **argv){
    test01();
    return 0;
}


