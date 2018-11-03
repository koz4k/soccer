#ifndef _soccer_AiStandalone_h_
#define _soccer_AiStandalone_h_

#include "Ai.h"
#include <memory>

namespace soccer {

class AiStandalone
{
  public:
  	AiStandalone(std::unique_ptr<Ai> ai);
  	void run();
  	
  private:
  	void boardsize_(int width, int height);
  	void timeleft_(int ms);
  	void play_(int direction);
  	int genmove_();
	int getTimeLeft_() const;
  	
    std::unique_ptr<Ai> ai_;
  	GameState state_;
  	int endTime_;
	bool initialized_;
};
	
}

#endif
