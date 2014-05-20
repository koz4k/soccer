#ifndef _Soccer_MaxOfFewSearch_h_
#define _Soccer_MaxOfFewSearch_h_

#include "HeuristicSearch.h"

namespace soccer { namespace ai {

class MaxOfFewSearch: public HeuristicSearch
{
  public:
  	MaxOfFewSearch(Heuristic heuristic, int k);
  	virtual Direction move(GameState& state, int ms
#ifdef DEBUG
						   , std::list<Direction>& moveSequence
#endif
  						  );
  						  
  private:
  	int k_;
};
	
} }

#endif