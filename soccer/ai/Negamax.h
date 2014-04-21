#ifndef _Soccer_Negamax__h_
#define _Soccer_Negamax__h_

#include "HeuristicSearch.h"
#include <list>

namespace soccer { namespace ai {

class Negamax: public HeuristicSearch
{
  public:
  	Negamax(Heuristic heuristic, int maxDepth);
  	virtual Direction move(const GameState& state, int ms);
  
  private:
  	double negamax_(GameState& state, std::list<Direction>& sequence,
  					bool saveSequence, int color, int depth);
  
  	int maxDepth_;
  	std::list<Direction> queue_;
};
	
} }

#endif