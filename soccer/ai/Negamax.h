#ifndef _Soccer_Negamax_h_
#define _Soccer_Negamax_h_

#include "HeuristicSearch.h"

namespace soccer { namespace ai {

class Negamax: public HeuristicSearch
{
  public:
  	Negamax(Heuristic heuristic, int maxDepth);
  	virtual Direction move(const GameState& state, int ms
#ifdef DEBUG
		, std::list<Direction>& moveSequence
#endif
  		);
  
  private:
  	double negamax_(GameState& state, int color, int depth, Direction& move
#ifdef DEBUG
  					, std::list<Direction>& sequence
#endif
  				   );
  
  	int maxDepth_;
};
	
} }

#endif
