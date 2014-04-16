#ifndef _Soccer_HeuristicSearch_h_
#define _Soccer_HeuristicSearch_h_

#include "../Ai.h"
#include <functional>

namespace soccer { namespace ai {

class HeuristicSearch: public Ai
{
  public:
  	typedef std::function<double(const GameState&)> Heuristic;
  
  	HeuristicSearch(Heuristic heuristic);
  	
  protected:
	Heuristic heuristic_;
};
	
} }

#endif
