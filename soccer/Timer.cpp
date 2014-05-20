#include "Timer.h"
#include <ctime>

namespace soccer {
	
Timer::Timer():
	endTime_(0)
{
}

Timer::Timer(int timeLeft):
	endTime_(0)
{
	setTimeLeft(timeLeft);
}

void Timer::setTimeLeft(int timeLeft)
{
	endTime_ = Timer::time() + timeLeft;
}

int Timer::operator()() const
{
	return endTime_ - Timer::time();
}

int Timer::time()
{
	return ((double) clock()) / CLOCKS_PER_SEC * 1000;
}
	
}