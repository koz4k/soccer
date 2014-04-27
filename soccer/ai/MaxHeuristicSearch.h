#ifndef _Soccer_ShallowHeuristicSearch_h_
#define _Soccer_ShallowHeuristicSearch_h_

#include "HeuristicSearch.h"

namespace soccer { namespace ai {

class MaxHeuristicSearch: public HeuristicSearch
{
  public:
  	MaxHeuristicSearch(Heuristic heuristic);
  	virtual Direction move(const GameState& state, int ms
#ifdef DEBUG
						   , std::list<Direction>& moveSequence
#endif
  						  );
};
	
} }

#endif