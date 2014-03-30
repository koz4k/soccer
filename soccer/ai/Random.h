#ifndef _Soccer_Random_h_
#define _Soccer_Random_h_

#include "../Ai.h"

namespace soccer { namespace ai {

class Random: public Ai
{
  public:
  	Random();
  	virtual Direction move(const GameState& state, int);
};
	
} }

#endif
