#include "smartUniform.h"

#include <cmath>

namespace soccer { namespace ai { namespace heur {
	
double smartUniform1(const GameState& state, int ms)
{
	return state.isGameOver() ? state.whoWon() == PLAYER_1 ? INFINITY : -INFINITY : 1;
}

double smartUniform2(const GameState& state, int ms)
{
	return state.isGameOver() ? state.whoWon() == PLAYER_2 ? INFINITY : -INFINITY : 1;
}

} } }