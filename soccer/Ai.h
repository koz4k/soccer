#ifndef _Soccer_Ai_h_
#define _Soccer_Ai_h_

#include "GameState.h"
#include <list>

namespace soccer {

class Ai
{
  public:
	virtual ~Ai() {}
#ifndef DEBUG
  	virtual Direction move(const GameState& state, int ms) = 0;
#else
  	virtual Direction move(const GameState& state, int ms, std::list<Direction>& moveSequence) = 0;
 	Direction move(const GameState& state, int ms);
 #endif
};

}

#endif