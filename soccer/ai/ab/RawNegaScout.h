#ifndef _Soccer_RawNegaScout_h_
#define _Soccer_RawNegaScout_h_

#include "../AlphaBeta.h"

namespace soccer { namespace ai { namespace ab {
	
class RawNegaScout: public AlphaBeta
{
  public:
  	RawNegaScout(Heuristic heuristic, int depth = 0);
  
  protected:
  	virtual double alphaBeta_(GameState& state, int color, int depth,
  					          double alpha, double beta, Direction& move
#ifdef DEBUG
  							  , std::list<Direction>& sequence
#endif
  				   			 );
};
	
} } }

#endif