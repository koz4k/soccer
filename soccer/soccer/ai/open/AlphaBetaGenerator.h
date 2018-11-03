#ifndef _soccer_AlphaBetaGenerator_h_
#define _soccer_AlphaBetaGenerator_h_

#include "Move.h"
#include "MyMove.h"
#include "YourMove.h"
#include "../../core.h"
#include "../AlphaBeta.h"
#include <memory>

namespace soccer { namespace ai { namespace open {
	
class AlphaBetaGenerator
{
  public:
  	AlphaBetaGenerator(int depth, int limit, Heuristic heuristic);
    std::unique_ptr<Move> generate(bool meFirst, double confidence);
  	
  private:
    std::unique_ptr<Move> generateMyMove_(GameState& state, int depth);
  	std::unique_ptr<Move> generateYourMove_(GameState& state, int depth);
  
    std::unique_ptr<AlphaBeta> ai_;
  	int depth_;
  	int limit_;
  	double confidence_;
};
	
} } }

#endif
