#ifndef _Soccer_AiStandalone_h_
#define _Soccer_AiStandalone_h_

#include "Ai.h"

namespace soccer {

class AiStandalone
{
  public:
  	AiStandalone(Ai* ai);
  	~AiStandalone();
  	void run();
  	
  private:
  	void boardsize_(int width, int height);
  	void timeleft_(int ms);
  	void play_(int direction);
  	int genmove_();
	int getTimeLeft_() const;
  	
  	Ai* ai_;
  	GameState state_;
  	int endTime_;
	bool initialized_;
};
	
}

#endif