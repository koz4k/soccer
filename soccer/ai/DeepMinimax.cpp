#include "DeepMinimax.h"
#include <algorithm>

//#include <CtrlLib/CtrlLib.h>

namespace soccer { namespace ai {

DeepMinimax::DeepMinimax(Heuristic heuristic, int maxDepth):
	HeuristicSearch(heuristic), maxDepth_(maxDepth)
{
}

Direction DeepMinimax::move(const GameState& state, int ms)
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
		double value = min_(validMoves[i].endState, maxDepth_);
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

double DeepMinimax::max_(const GameState& state, int depth)
{
	if(state.isGameOver() || !depth)
		return heuristic_(state);
	
	std::vector<GameState::Move> validMoves = state.getValidMoves();
	double bestValue = -INFINITY;
	for(int i = 0; i < validMoves.size(); ++i)
		bestValue = std::max(min_(validMoves[i].endState, depth - 1), bestValue);
	
	return bestValue;
}

double DeepMinimax::min_(const GameState& state, int depth)
{
	if(state.isGameOver() || !depth)
		return heuristic_(state);
	
	std::vector<GameState::Move> validMoves = state.getValidMoves();
	double bestValue = INFINITY;
	for(int i = 0; i < validMoves.size(); ++i)
		bestValue = std::min(max_(validMoves[i].endState, depth - 1), bestValue);
	
	return bestValue;
}
	
} }
