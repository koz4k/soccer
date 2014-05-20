#ifndef _Soccer_ReboundAwareNaive_h_
#define _Soccer_ReboundAwareNaive_h_

#include "../../GameState.h"

namespace soccer { namespace ai { namespace heur {
	
class ReboundAwareNaive
{
  public:
  	ReboundAwareNaive(double reboundWeight, Player player);
  	double operator()(const GameState& state);
  	
  private:
  	double r_;
  	Player player_;
};
	
} } }

#endif