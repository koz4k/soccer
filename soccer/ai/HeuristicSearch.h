#ifndef _Soccer_HeuristicSearch_h_
#define _Soccer_HeuristicSearch_h_

#include "../Ai.h"
#include <functional>

namespace soccer { namespace ai {

typedef std::function<double(const GameState& state, int ms)> Heuristic;

class HeuristicSearch: public Ai
{
  public:  
  	HeuristicSearch(Heuristic heuristic);
  	
  protected:
	Heuristic heuristic_;
};
	
} }

#endif
