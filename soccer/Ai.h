#ifndef _Soccer_Ai_h_
#define _Soccer_Ai_h_

#include "GameState.h"
#include <list>

namespace soccer {

class Ai
{
  public:
	Ai();
	virtual ~Ai();
#ifndef DEBUG
  	virtual Direction move(GameState& state, int ms) = 0;
#else
  	virtual Direction move(GameState& state, int ms, std::list<Direction>& moveSequence) = 0;
 	Direction move(GameState& state, int ms);
 #endif
 	virtual void opponentMoved(Direction direction);
 	virtual void reset();
 	double getConfidence() const; // zwraca miare "pewnosci" ostatniego ruchu - do otwarc
 	
  protected:
  	double confidence_;
};

}

#endif