#ifndef _Soccer_Ai_h_
#define _Soccer_Ai_h_

#include "GameState.h"

namespace soccer {

class Ai
{
  public:
  	virtual Direction move(const GameState& state, int ms) = 0;
};

}

#endif
