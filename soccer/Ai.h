#ifndef _Soccer_Ai_h_
#define _Soccer_Ai_h_

#include "GameState.h"
#include <list>

namespace soccer {

class Ai
{
  public:
  	virtual Direction move(const GameState& state, int ms
#ifdef DEBUG
						   , std::list<Direction>& moveSequence
#endif
  		                  ) = 0;
};

}

#endif