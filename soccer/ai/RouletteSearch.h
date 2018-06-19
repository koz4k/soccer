#ifndef _soccer_RouletteSearch_h_
#define _soccer_RouletteSearch_h_

#include "HeuristicSearch.h"

namespace soccer { namespace ai {

class RouletteSearch: public HeuristicSearch
{
  public:
  	RouletteSearch(Heuristic heuristic, double lambda);
  	virtual Direction move(GameState& state, int ms
#ifdef DEBUG
						   , std::list<Direction>& moveSequence
#endif
  						  );
  
  private:
  	double lambda_;
};
	
} }

#endif