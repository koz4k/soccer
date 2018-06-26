#include "naive.h"
#include <algorithm>
#include <cmath>
#include <limits>

namespace soccer { namespace ai { namespace heur {

double naive1(const GameState& state)
{
	Vector2 position = state.getCurrentPosition();
	
	if(state.isGameOver())
		return state.whoWon() == PLAYER_1 ? std::numeric_limits<double>::infinity()
                                          :-std::numeric_limits<double>::infinity();
	
	return position.y;
}

double naive2(const GameState& state)
{
	Vector2 position = state.getCurrentPosition();
	
	if(state.isGameOver())
		return state.whoWon() == PLAYER_2 ? std::numeric_limits<double>::infinity()
                                          :-std::numeric_limits<double>::infinity();
	
	return -position.y;
}

double safe1(const GameState& state)
{
	Vector2 position = state.getCurrentPosition();
	
	if(state.isGameOver())
		return state.whoWon() == PLAYER_1 ? std::numeric_limits<double>::infinity()
                                          : -std::numeric_limits<double>::infinity();
	
	return std::max(6 + position.y, std::abs(position.x)) -
		   std::max(6 - position.y, std::abs(position.x));
}

double safe2(const GameState& state)
{
	Vector2 position = state.getCurrentPosition();
	
	if(state.isGameOver())
		return state.whoWon() == PLAYER_2 ? std::numeric_limits<double>::infinity()
                                          : -std::numeric_limits<double>::infinity();
	
	return std::max(6 - position.y, std::abs(position.x)) -
		   std::max(6 + position.y, std::abs(position.x));
}

double risky1(const GameState& state)
{
	Vector2 position = state.getCurrentPosition();
	
	if(state.isGameOver())
		return state.whoWon() == PLAYER_1 ? std::numeric_limits<double>::infinity()
                                          : -std::numeric_limits<double>::infinity();
	
	return std::max(6 + position.y, -std::abs(position.x)) -
		   std::max(6 - position.y, -std::abs(position.x));
}

double risky2(const GameState& state)
{
	Vector2 position = state.getCurrentPosition();
	
	if(state.isGameOver())
		return state.whoWon() == PLAYER_2 ? std::numeric_limits<double>::infinity()
                                          : -std::numeric_limits<double>::infinity();
	
	return std::max(6 - position.y, -std::abs(position.x)) -
		   std::max(6 + position.y, -std::abs(position.x));
}

} } }
