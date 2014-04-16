#ifndef _Soccer_Greedy_h_
#define _Soccer_Greedy_h_

#include "HeuristicSearch.h"

namespace soccer { namespace ai {

class Greedy: public HeuristicSearch
{
  public:
  	Greedy(Heuristic heuristic);
  	virtual Direction move(const GameState& state, int ms);
};
	
} }

#endif
