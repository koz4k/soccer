#ifndef _Soccer_Uniform_h_
#define _Soccer_Uniform_h_

#include "../TimingStrategy.h"

namespace soccer { namespace timing {

class Uniform: public TimingStrategy
{
  public:
  	Uniform(double multiplier = 1.0, int timeMargin = 1, int moveCount = 336);
  	virtual void setGameState(const GameState& state);

  protected:
  	virtual double allocateTime_();
  	
  private:
  	double mul_;
	int moveCount_;
  	int movesLeft_;
};
	
} }

#endif