#include "naive.h"
#include <algorithm>
#include <cmath>

namespace soccer { namespace ai { namespace heur {

double naive1(const GameState& state)
{
	Vector2 position = state.getCurrentPosition();
	
	if(state.isGameOver())
		return state.whoWon() == PLAYER_1 ? INFINITY : -INFINITY;
	
	return std::max(6 + position.y, -std::abs(position.x)) -
		   std::max(6 - position.y, -std::abs(position.x));
}

double naive2(const GameState& state)
{
	Vector2 position = state.getCurrentPosition();
	
	if(state.isGameOver())
		return state.whoWon() == PLAYER_2 ? INFINITY : -INFINITY;
	
	return std::max(6 - position.y, -std::abs(position.x)) -
		   std::max(6 + position.y, -std::abs(position.x));
}

} } }