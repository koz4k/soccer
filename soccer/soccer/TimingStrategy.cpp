#include "TimingStrategy.h"

namespace soccer {

TimingStrategy::TimingStrategy(int timeMargin):
	timeMargin_(timeMargin), timeLeft_(0)
{
}

int TimingStrategy::getTimeLeft() const
{
	return timeLeft_;
}

void TimingStrategy::setTimeLeft(int timeLeft)
{
	timeLeft_ = timeLeft;
}

void TimingStrategy::start(int timeLeft)
{
	if(timeLeft != -1)
		setTimeLeft(timeLeft);
	
	int allocated = timeLeft_ * allocateTime_();
	timer_.setTimeLeft(allocated);
	timeLeft_ -= allocated;
}

void TimingStrategy::stop()
{
	timeLeft_ += timer_();
}

void TimingStrategy::setGameState(const GameState& state)
{
}

int TimingStrategy::getTimeAvailable() const
{
	return timer_();
}

bool TimingStrategy::haveTime() const
{
	return getTimeAvailable() >= timeMargin_;
}
	
}