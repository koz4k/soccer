#include "DeepNegamax.h"
#include <algorithm>

namespace soccer { namespace ai {

DeepNegamax::DeepNegamax(Heuristic heuristic, int maxDepth):
	HeuristicSearch(heuristic), maxDepth_(maxDepth)
{
}

Direction DeepNegamax::move(const GameState& state, int ms)
{
	if(!queue_.empty())
	{
		Direction direction = queue_.back();
		queue_.pop_back();
		return direction;
	}
	
	std::vector<GameState::Move> validMoves = state.getValidMoves();
	int bestMove = -1;
	double bestValue = -INFINITY;
	for(int i = 0; i < validMoves.size(); ++i)
	{
		double value = -negamax_(validMoves[i].endState, -1, maxDepth_);
		if(value > bestValue || bestMove == -1)
		{
			bestMove = i;
			bestValue = value;
		}
	}
	
	queue_ = validMoves[bestMove].sequence;
	std::reverse(queue_.begin(), queue_.end());
	Direction direction = queue_.back();
	queue_.pop_back();
	return direction;
}

double DeepNegamax::negamax_(const GameState& state, int color, int depth)
{
	if(state.isGameOver() || !depth)
		return heuristic_(state) * color;
	
	std::vector<GameState::Move> validMoves = state.getValidMoves();
	double bestValue = -INFINITY;
	for(int i = 0; i < validMoves.size(); ++i)
		bestValue = std::max(-negamax_(validMoves[i].endState, -color, depth - 1), bestValue);
	
	return bestValue;
}
	
} }
