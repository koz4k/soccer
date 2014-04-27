#ifndef _Soccer_RandomHeuristicSearch_h_
#define _Soccer_RandomHeuristicSearch_h_

#include "HeuristicSearch.h"

namespace soccer { namespace ai {

class RandomHeuristicSearch: public HeuristicSearch
{
  public:
  	RandomHeuristicSearch(Heuristic heuristic, double lambda);
  	virtual Direction move(const GameState& state, int ms
#ifdef DEBUG
						   , std::list<Direction>& moveSequence
#endif
  						  );
  
  private:
  	double lambda_;
};
	
} }

#endif