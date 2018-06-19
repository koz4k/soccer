#ifndef _soccer_Naive_h_
#define _soccer_Naive_h_

#include "../../GameState.h"

namespace soccer { namespace ai { namespace heur {
	
double naive1(const GameState& state);
double naive2(const GameState& state);
double safe1(const GameState& state);
double safe2(const GameState& state);
double risky1(const GameState& state);
double risky2(const GameState& state);
	
} } }

#endif