 ///
 /// @file    Timerfd.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-07-19 10:21:40
 ///
 
#include "Timerfd.h"

#include <unistd.h>
#include <poll.h>
#include <sys/timerfd.h>

#include <iostream>
using std::cout;
using std::endl;
 
namespace wd
{

Timerfd::Timerfd(int initialTime, int intervalTime, TimerCallback && cb)
: _fd(createTimerfd())
, _initialTime(initialTime)
, _intervalTime(intervalTime)
, _cb(std::move(cb))
, _isStarted(false)
{}

void Timerfd::start()
{
	_isStarted = true;

	struct pollfd pfd;
	pfd.fd = _fd;
	pfd.events = POLLIN;

	setTimerfd(_initialTime, _intervalTime);

	while(_isStarted) {
		int nready = ::poll(&pfd, 1, -1);	
		if(nready == -1 && errno == EINTR)
			continue;
		else if(nready == -1)
			return;
		else if(nready == 0)
			printf(">> poll timeout!!\n");
		else {
			if(pfd.revents & POLLIN) {
				handleRead();
				if(_cb)
					_cb();
			}
            cout<<"cache update"<<endl;
		}
	}
}

void Timerfd::stop()
{
	if(_isStarted) {
		_isStarted = false;
		setTimerfd(0, 0);
	}
}

int Timerfd::createTimerfd()
{
	int fd = ::timerfd_create(CLOCK_REALTIME, 0);
	if(fd == -1) {
		perror(">> timerfd_create");
	}
	return fd;
}
	
void Timerfd::setTimerfd(int initialTime, int intervalTime)
{
	struct itimerspec value;
	value.it_value.tv_sec = initialTime;
	value.it_value.tv_nsec = 0;
	value.it_interval.tv_sec = intervalTime;
	value.it_interval.tv_nsec = 0;

	int ret = ::timerfd_settime(_fd, 0, &value, nullptr);
	if(ret == -1) {
		perror(">> timerfd_settime");
	}
}


void Timerfd::handleRead()
{
	uint64_t howmany;
	int ret = ::read(_fd, &howmany, sizeof(uint64_t));
	if(ret != sizeof(howmany)) {
		perror(">> read");
	}
}
}//end of namespace wd
