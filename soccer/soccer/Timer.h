#ifndef _soccer_Timer_h_
#define _soccer_Timer_h_

namespace soccer {

class Timer
{
  public:
	Timer();
  	explicit Timer(int timeLeft);
	void setTimeLeft(int timeLeft);
  	int operator()() const;
  	
  	static int time();
  	
  private:
  	int endTime_;
};
	
}

#endif