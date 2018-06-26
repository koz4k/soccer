#ifndef _soccer_HeuristicSearch_h_
#define _soccer_HeuristicSearch_h_

#include "../Ai.h"
#include "../core.h"
#include <functional>

#include <list>

namespace soccer { namespace ai {

class HeuristicSearch: public Ai
{
  public:  
  	HeuristicSearch(Heuristic heuristic);
  	
  protected:
	Heuristic heuristic_;
};
	
} }

#endif