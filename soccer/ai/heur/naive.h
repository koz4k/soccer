#ifndef _Soccer_Naive_h_
#define _Soccer_Naive_h_

#include "../../GameState.h"

namespace soccer { namespace ai { namespace heur {
	
double naive1(const GameState& state, int ms);
double naive2(const GameState& state, int ms);
	
} } }

#endif