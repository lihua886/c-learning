#pragma  once
#include "GameTime.h"
#include "Headquarters.h"
#include "HeadquarterView.h"
#include "City.h"
#include <memory>
#include <vector>


namespace warcraft
{

//class Headquarters;
//class RedHeadquarters;
//class BlueHeadquarters;
class Warrior;
class WarcraftWorld
{
public:
    using WarriorPtr=std::shared_ptr<warcraft::Warrior>;
    explicit
        WarcraftWorld()
        : _redHeadquarters(nullptr)
          , _blueHeadquarters(nullptr)
    { init();  }
    void start()//游戏开始
    {
        while(1) {
            createWarrior();
            GameTime::getInstance()->updateTime();
            if(!warriorMarch())
              { 
                  showMarch(); 
                  break;  
              }
            showMarch();
            GameTime::getInstance()->updateTime();
            cityProduceElements();
            GameTime::getInstance()->updateTime();
            takeCityElements();
            GameTime::getInstance()->updateTime();
            battle();
            GameTime::getInstance()->updateTime();
            headquartersReportElements();
            GameTime::getInstance()->updateTime();
        }
        HeadquartersView headView(_redHeadquarters);
        if(checkRedHeadquartersBeTaken()){
            headView.showBeTaken();
        }  
        HeadquartersView headView1(_blueHeadquarters);
        if(checkBlueHeadquartersBeTaken()){
            headView1.showBeTaken();
        }  
    }
    template <typename Iterator>
        void setRedWarriorCreatingOrder(Iterator beg, Iterator end);
    template <typename Iterator>
        void setBlueWarriorCreatingOrder(Iterator beg, Iterator end);
    ~WarcraftWorld()
    {
        if(_redHeadquarters) delete _redHeadquarters;
        if(_blueHeadquarters) delete _blueHeadquarters;
        
    }
private:
    void init();
    void March(WarriorPtr);
    void showMarch();
    void displayWarrior();
    //------------事件begin-----------
    void createWarrior(); //整点：创建武士
    bool warriorMarch();//第10分: 武士行军
    void cityProduceElements(); //第20分：城市生产生命元
    void takeCityElements(); //第30分：武士取走城市中的生命元
    void battle(); //第40分：战斗
    void headquartersReportElements(); //第50分：司令部报告情况
    //------------事件end ------------
    bool createWarrior(warcraft::Headquarters *);//某个司令部开始创建武士
    void warriorMarch(warcraft::Headquarters * headquarters);//某个司令部中的武士行
    //军
    bool checkRedHeadquartersBeTaken();//判断红司令部是否被占领
    bool checkBlueHeadquartersBeTaken();//判断蓝司令部是否被占领
private:
    Headquarters * _redHeadquarters;//红色司令部
    Headquarters * _blueHeadquarters;//蓝色司令部
    std::vector<City> _cities;//所有的城市,其中 0号代表红色司令部， size - 1 代表
    //蓝色司令部
};


template <typename Iterator>
void WarcraftWorld::setRedWarriorCreatingOrder(Iterator beg, Iterator end)
{
    _redHeadquarters->setWarriorCreatingOrder(beg, end);
}

template <typename Iterator>
void WarcraftWorld::setBlueWarriorCreatingOrder(Iterator beg, Iterator end)
{
    _blueHeadquarters->setWarriorCreatingOrder(beg, end);
    
}



}// end of warcraft
