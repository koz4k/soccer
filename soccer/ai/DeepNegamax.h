#ifndef _Soccer_DeepNegamax_h_
#define _Soccer_DeepNegamax_h_

#include "HeuristicSearch.h"

namespace soccer { namespace ai {

class DeepNegamax: public HeuristicSearch
{
  public:
  	DeepNegamax(Heuristic heuristic, int maxDepth);
  	virtual Direction move(const GameState& state, int ms);
  
  private:
  	double negamax_(const GameState& state, int color, int depth);
  
  	int maxDepth_;
  	std::vector<Direction> queue_;
};
	
} }

#endif