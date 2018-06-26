#ifndef _soccer_DeepMaxOfFewSearch_h_
#define _soccer_DeepMaxOfFewSearch_h_

#include "HeuristicSearch.h"
#include <queue>

namespace soccer { namespace ai {

class DeepMaxOfFewSearch: public HeuristicSearch
{
  public:
  	DeepMaxOfFewSearch(Heuristic heuristic, int k);
  	virtual Direction move(GameState& state, int ms
#ifdef DEBUG
						   , std::list<Direction>& moveSequence
#endif
  						  );
  						  
  private:
  	double generate_(GameState& state, std::queue<Direction>& moves, bool first = true);
  
  	int k_;
  	std::queue<Direction> queue_;
};
	
} }

#endif