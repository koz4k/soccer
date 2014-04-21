#ifndef _Soccer_ShallowHeuristicSearch_h_
#define _Soccer_ShallowHeuristicSearch_h_

#include "HeuristicSearch.h"

namespace soccer { namespace ai {

class ShallowHeuristicSearch: public HeuristicSearch
{
  public:
  	ShallowHeuristicSearch(Heuristic heuristic);
  	virtual Direction move(const GameState& state, int ms);
};
	
} }

#endif