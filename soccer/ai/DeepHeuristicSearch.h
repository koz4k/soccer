#ifndef _Soccer_DeepHeuristicSearch_h_
#define _Soccer_DeepHeuristicSearch_h_

#include "HeuristicSearch.h"

namespace soccer { namespace ai {

class DeepHeuristicSearch: public HeuristicSearch
{
  public:
  	DeepHeuristicSearch(Heuristic heuristic);
  	virtual Direction move(const GameState& state, int ms);
  
  private:
  	std::vector<Direction> queue_;
};
	
} }

#endif