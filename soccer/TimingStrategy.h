#ifndef _Soccer_TimingStrategy_h_
#define _Soccer_TimingStrategy_h_

#include "Timer.h"
#include "GameState.h"

namespace soccer {

class TimingStrategy
{
  public:
  	TimingStrategy(int timeMargin = 1);
  	int getTimeLeft() const;
  	void setTimeLeft(int timeLeft);
  	void start(int timeLeft = -1);
  	void stop();
  	virtual void setGameState(const GameState& state);
  	int getTimeAvailable() const;
  	bool haveTime() const;
  
  protected:
  	virtual double allocateTime_() = 0;
  
	int timeMargin_;
  	int timeLeft_;
  	Timer timer_;
};
	
}

#endif