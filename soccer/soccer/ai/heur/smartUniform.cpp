#include "smartUniform.h"
#include <limits>

#include <cmath>

namespace soccer { namespace ai { namespace heur {
	
double smartUniform1(const GameState& state)
{
	return state.isGameOver() ?
        state.whoWon() == PLAYER_1 ? std::numeric_limits<double>::infinity()
                                   : -std::numeric_limits<double>::infinity() : 1;
}

double smartUniform2(const GameState& state)
{
	return state.isGameOver() ?
        state.whoWon() == PLAYER_2 ? std::numeric_limits<double>::infinity()
                                   : -std::numeric_limits<double>::infinity() : 1;
}

} } }
