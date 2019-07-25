 ///
 /// @file    Timerfd.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-07-19 10:19:01
 ///
 
#pragma once

#include <iostream>
#include <functional>
using std::cout;
using std::endl;
using std::function;
 

namespace wd
{

class Timerfd
{
public:
	using TimerCallback = function<void()>; 
	
	Timerfd(int initialTime, int intervalTime, TimerCallback && cb);

	void start();
	void stop();

private:
	int createTimerfd();
	void setTimerfd(int initialTime, int intervalTime);
	void handleRead();

private:
	int _fd;
	int _initialTime;
	int _intervalTime;
	TimerCallback _cb;
	bool _isStarted;
};

}//end of namespace wd
