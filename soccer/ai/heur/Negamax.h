#ifndef _Soccer_Negamax_h_
#define _Soccer_Negamax_h_

#include "../HeuristicSearch.h"
#include "../../GameState.h"

namespace soccer { namespace ai { namespace heur {
	
class Negamax
{
  public:
  	Negamax(Heuristic heuristic, int maxDepth);
  	double operator()(const GameState& state, int ms);
  	
  private:
  	double negamax_(GameState& state, int color, int depth);
  
  	Heuristic heuristic_;
  	int maxDepth_;
};
	
} } }

#endif