#include "DeepMaxOfFewSearch.h"
#include <cstdlib>
#include <ctime>
#include <cmath>

namespace soccer { namespace ai {

DeepMaxOfFewSearch::DeepMaxOfFewSearch(Heuristic heuristic, int k):
	HeuristicSearch(heuristic), k_(k)
{
	//srand(time(nullptr));
}

Direction DeepMaxOfFewSearch::move(GameState& state, int ms
#ifdef DEBUG
					   			   , std::list<Direction>& moveSequence
#endif
					  			  )
{
	if(queue_.empty())
	{
		double bestValue = -INFINITY;
		for(int i = 0; i < k_; ++i)
		{
			std::queue<Direction> moves;
			double value = generate_(state, moves);
			if(value > bestValue || queue_.empty())
			{
				bestValue = value;
				queue_ = std::move(moves);
			}
		}
	}
	
	Direction move = queue_.front();
	queue_.pop();
#ifdef DEBUG
	moveSequence.clear();
	moveSequence.push_back(move);
#endif
	return move;
}
					  
double DeepMaxOfFewSearch::generate_(GameState& state, std::queue<Direction>& moves, bool first)
{
	if((!first && !state.canRebound()) || state.isGameOver())
		return heuristic_(state);
	
	Direction move = DIR_END;
	do
	{
		move = rand() % DIR_END;
	}
	while(!state.canMove(move));
	
	state.move(move);
	moves.push(move);
	double value = generate_(state, moves, false);
	state.undo(move);
	
	return value;
}
	
} }