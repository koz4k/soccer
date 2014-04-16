#ifndef _Soccer_Minimax_h_
#define _Soccer_Minimax_h_

#include "HeuristicSearch.h"

namespace soccer { namespace ai {

class DeepMinimax: public HeuristicSearch
{
  public:
  	DeepMinimax(Heuristic heuristic, int maxDepth);
  	virtual Direction move(const GameState& state, int ms);
  
  private:
  	double max_(const GameState& state, int depth);
  	double min_(const GameState& state, int depth);
  
  	int maxDepth_;
  	std::vector<Direction> queue_;
};
	
} }

#endif
