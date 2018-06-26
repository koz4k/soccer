#ifndef _soccer_MaxSearch_h_
#define _soccer_MaxSearch_h_

#include "HeuristicSearch.h"

namespace soccer { namespace ai {

class MaxSearch: public HeuristicSearch
{
  public:
  	MaxSearch(Heuristic heuristic);
  	virtual Direction move(GameState& state, int ms
#ifdef DEBUG
						   , std::list<Direction>& moveSequence
#endif
  						  );
};
	
} }

#endif