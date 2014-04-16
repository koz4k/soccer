#ifndef _Soccer_DeepGreedy_h_
#define _Soccer_DeepGreedy_h_

#include "HeuristicSearch.h"

namespace soccer { namespace ai {

class DeepGreedy: public HeuristicSearch
{
  public:
  	DeepGreedy(Heuristic heuristic);
  	virtual Direction move(const GameState& state, int ms);
  
  private:
  	std::vector<Direction> queue_;
};
	
} }

#endif