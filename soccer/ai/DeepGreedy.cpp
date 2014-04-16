#include "DeepGreedy.h"
#include <algorithm>

namespace soccer { namespace ai {

DeepGreedy::DeepGreedy(Heuristic heuristic):
	HeuristicSearch(heuristic)
{
}

Direction DeepGreedy::move(const GameState& state, int ms)
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
		double value = heuristic_(validMoves[i].endState);
		if(value > bestValue)
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
	
} }
