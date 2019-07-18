#pragma once

#include "type.h"
#include <iostream>
#include <vector>
#include <memory>

namespace warcraft{
class Warrior;

class City{
using WarriorPtr=std::shared_ptr<warcraft::Warrior>;
public:
    City(size_t id, size_t elements = 0)
        : _flag(Color::NOTSET)
          , _id(id)
          , _elements(elements)
          , _redWinCount(0)
          , _blueWinCount(0){}
    void produceElements();//城市生产生命元
    void attach(WarriorPtr);//某武士进入该城市
    void detach(WarriorPtr);//某武士离开该城市
    void startBattle();//开始战斗
    void takenBy(WarriorPtr warrior);//生命元被某武士取走
    size_t getId() const { return _id;  }
    Color getFlag() const { return _flag;  }
    size_t getWarriorAmount() const{ 
        return _redWarriors.size() + _blueWarriors.size();  
    }
    std::vector<WarriorPtr> & getRedWarriors() { 
        return _redWarriors;  
    }
    std::vector<WarriorPtr> & getBlueWarriors() { 
        return _blueWarriors; 
    }
private:
    void battle(WarriorPtr warrior1, WarriorPtr warrior2);//2名武士的具体战斗状况
    bool isChangingFlag(WarriorPtr warrior);//是否更换旗子
private:Color _flag;//城市旗子的颜色
        size_t _id;//城市编号
        size_t _elements;//城市生命元
        size_t _redWinCount;//红魔军连续胜利次数
        size_t _blueWinCount;//蓝魔军连续胜利次数
        std::vector<WarriorPtr> _redWarriors;
        std::vector<WarriorPtr> _blueWarriors;
};



}
