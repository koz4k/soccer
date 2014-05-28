#ifndef _Soccer_AlphaBetaGenerator_h_
#define _Soccer_AlphaBetaGenerator_h_

#include "Move.h"
#include "MyMove.h"
#include "YourMove.h"
#include "../../core.h"
#include "../AlphaBeta.h"

namespace soccer { namespace ai { namespace open {
	
class AlphaBetaGenerator
{
  public:
  	AlphaBetaGenerator(int depth, int limit, Heuristic heuristic);
  	~AlphaBetaGenerator();
  	Move* generate(bool meFirst, double confidence);
  	
  private:
  	MyMove* generateMyMove_(GameState& state, int depth);
  	YourMove* generateYourMove_(GameState& state, int depth);
  
  	AlphaBeta* ai_;
  	int depth_;
  	int limit_;
  	double confidence_;
};
	
} } }

#endif