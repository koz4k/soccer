#include "DeepHeuristicSearch.h"
#include <algorithm>

namespace soccer { namespace ai {

DeepHeuristicSearch::DeepHeuristicSearch(Heuristic heuristic):
	HeuristicSearch(heuristic)
{
}

Direction DeepHeuristicSearch::move(const GameState& state, int ms)
{
	if(!queue_.empty())
	{
		Direction direction = queue_.back();
		queue_.pop_back();
		return direction;
	}
	
	std::vector<GameState::Move> validMoves = state.getValidMoves();
	std::vector<int> permutation(validMoves.size());
	for(int i = 0; i < validMoves.size(); ++i)
		permutation[i] = i;
	std::random_shuffle(permutation.begin(), permutation.end());
	
	int bestMove = -1;
	double bestValue = -INFINITY;
	for(int i = 0; i < validMoves.size(); ++i)
	{
		int index = permutation[i];
		double value = heuristic_(validMoves[index].endState, 0);
		if(value > bestValue || bestMove == -1)
		{
			bestMove = index;
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