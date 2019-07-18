#pragma once

#define  __TRACE(...) fprintf(stdout, "file[%s]line[%u]func[%s]::",__FILE__,__LINE__,__func__);\
    fprintf(stdout,__VA_ARGS__)
#include "type.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>
#include <memory>
#include <fstream>


namespace warcraft
{

class GameConfig
{
public:
    static GameConfig * getInstance(){
        if(_pInstance==nullptr){
            _pInstance=new GameConfig;
            atexit(destroy);
        }
        return _pInstance;
    }
    static void destroy(){
        if(_pInstance){
            delete _pInstance;
            _pInstance=nullptr;
        }
    }
    void readFromConsole(){
         readFromStream(std::cin);
    }//从控制台终端获取测试数据
    void readFromFile(const std::string & filename){
         std::ifstream ifs(filename);
         readFromStream(ifs);
    }//从配置文件中获取测试数据
    void nextGroupId() { ++_currentGroupId;  }//测试下一组数据
    size_t groups() const { return _groups.size();  }
    size_t currentGroupId() const { return _currentGroupId+1;  }
    size_t cityCount() const{
        return _groups[_currentGroupId]._cityCount;
    }
    size_t headquartersInitialElements() const{
        return _groups[_currentGroupId]._initElements;
    }
    size_t warriorInitalLife(WarriorType key) {
        return _groups[_currentGroupId]._initLifes[key];
    }
    size_t warriorInitalAttack(WarriorType key) {
        return _groups[_currentGroupId]._initAttacks[key];
    }
    template<class Iterator>
    void setWarriorOrder(Iterator begin,Iterator end){
       _initWarriorOrder.assign(begin,end);
    }
private:
    GameConfig() 
    : _currentGroupId(0){ 
        std::cout << "GameConfig()" <<std::endl; 
    }
    ~GameConfig(){ 
        std::cout << "~GameConfig()" << std::endl;  
    }
    void readFromStream(std::istream & is){
//     __TRACE("is start!\n");
     int groups=0;
     is>>groups;
     for(int  i=0;i<groups;++i){
         InitData data;
         is>>data._initElements>>data._cityCount>>data._minutes;
         for(auto &it:_initWarriorOrder){
              is>>data._initLifes[it];
         //     std::cout<<"life:"<<data._initLifes[it]<<std::endl;
         }   
         for(auto &it:_initWarriorOrder){
              is>>data._initAttacks[it];
          //    std::cout<<"attack:"<<data._initAttacks[it]<<std::endl;
         }   
         _groups.push_back(std::move(data));
     }
}
    struct InitData
    {
        size_t _initElements;
        size_t _cityCount;
        size_t _minutes;
        std::map<WarriorType, size_t> _initLifes;
        std::map<WarriorType, size_t> _initAttacks;

    };
private:
    static GameConfig * _pInstance;
    std::vector<InitData> _groups;//N组数据
    size_t _currentGroupId;//当前正在测试的一组数据
    std::vector<WarriorType> _initWarriorOrder;//输入时武士的生命值和攻击力的设置顺序
};


}
