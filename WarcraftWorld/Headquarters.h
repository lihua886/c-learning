#pragma  once
#include "GameConfig.h"
#include "GameTime.h"
#include "type.h"
#include "Warrior.h"
#include <map>
#include <vector>
#include <queue>
#include <unordered_map>
#include <memory>


namespace warcraft
{
//class Warrior;
class Headquarters
{
public:
    using WarriorPtr=std::shared_ptr<warcraft::Warrior>;
    struct WarriorCompare{
        bool operator()(WarriorPtr lhs,WarriorPtr rhs)const {
            if(lhs->getColor()==RED){
                return lhs->getCityId()<rhs->getCityId();
            }else{
                return lhs->getCityId()>rhs->getCityId();
            }
        }
    };
    Headquarters(Color color, size_t elements)
        : _color(color)
          ,_elements(elements)
          ,_earnElements(0)  //获得的生命元
          ,_nextWarriorIndex(0)// 下个生产的武士编号
    {}
    virtual ~Headquarters() {}
    //创建武士
    WarriorPtr create();
    //添加胜利者
    void addWinner(WarriorPtr warrior);
    //奖励胜利者
    void reward();
    //统计从城市获取的生命元
    void increaseElements(size_t elements) { 
        _earnElements +=elements;
    }
    void addElements(){
        _elements += _earnElements;
        _earnElements=0;
    }
    //设置所剩生命元的数量
    void setElements(size_t elements) { _elements = elements;  }

    template <typename Iterator>
    void setWarriorCreatingOrder(Iterator begin, Iterator end)
    { //设置武士生产顺序
        for(; begin != end; ++begin) {
            _warriorCreatingOrder.push_back(*begin);
        }
    }
    size_t getEarnElements(){return _earnElements;}
    size_t getId() const { return _id;  }
    void setId(size_t id) { _id = id;  }
    Color getColor() const { return _color;  }
    size_t getElements() const { return _elements;  }
    // 获取所有武士
    std::vector<WarriorPtr> & getWarriors() { return _warriors;  }
private:
    //生产各种武士
    WarriorPtr createIceman(size_t id, size_t hp, size_t forces);
    WarriorPtr createLion(size_t id, size_t hp, size_t forces);
    WarriorPtr createWolf(size_t id, size_t hp, size_t forces);
    WarriorPtr createNinja(size_t id, size_t hp, size_t forces);
    WarriorPtr createDragon(size_t id, size_t hp, size_t forces);
    WarriorType getNextWarriorType()
    { 
        return _warriorCreatingOrder[_nextWarriorIndex%_warriorCreatingOrder.size()];  
    }
protected:
    Color _color;//红或者蓝
    size_t _id;//编号, 0代表红色司令部, N+1 代表蓝色司令部
    size_t _elements;//当前司令部所剩的生命元
    size_t _earnElements;//一次战斗时刻结束后，所有武士获取的生命元
    size_t _nextWarriorIndex;//下次带生产的武士下标
    std::vector<WarriorType> _warriorCreatingOrder;//武士生产顺序
    //一次战斗时间结束后，胜利的所有武士
    std::priority_queue<WarriorPtr,std::vector<WarriorPtr>,WarriorCompare>
    _winners;
    std::vector<WarriorPtr> _warriors;//生产的所有武士
    //各种类型武士的数量
    std::unordered_map<WarriorType, size_t> _warriorTypeAmounts;
};
class RedHeadquarters
: public Headquarters
{
public:
    RedHeadquarters(size_t elements)
    : Headquarters(RED, elements){}
};
class BlueHeadquarters
: public Headquarters
{
public:
    BlueHeadquarters(size_t elements)
    : Headquarters(BLUE, elements){}
};


}

