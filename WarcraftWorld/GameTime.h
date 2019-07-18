#pragma once
#include <stdio.h>
#include <cstdlib>
#include <iostream>


namespace warcraft
{
class GameTime
{
public:
    static GameTime * getInstance(){
        if(_pInstance==nullptr){
            _pInstance=new GameTime;
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
    void showTime() const{
        printf("%03ld:%02ld",_hour,_minute);
    }//打印时间
    void updateTime(){
        _minute +=10;
        if(_minute==60){
            _hour++;
            _minute=0;
        }
    }//更新时间
    void reset() { _hour = 0; _minute = 0;  } // 重置 时间
    size_t  getMinute() {  return _minute; }
private:
        GameTime(size_t hour = 0, size_t minute = 0)
            : _hour(hour)
              , _minute(minute){
                  std::cout<<"GameTime()"<<std::endl;
              }
        ~GameTime(){
            std::cout<<"~GameTime()"<<std::endl;
        }
private:
        static GameTime * _pInstance;
        size_t _hour;
        size_t _minute;
};

}
