#include "MaxHeuristicSearch.h"
#include <algorithm>

namespace soccer { namespace ai {

MaxHeuristicSearch::MaxHeuristicSearch(Heuristic heuristic):
	HeuristicSearch(std::move(heuristic))
{
}

Direction MaxHeuristicSearch::move(const GameState& state, int ms
#ifdef DEBUG
								   , std::list<Direction>& moveSequence
#endif
  		                          )
{
	int bestMove = DIR_END;
	double bestValue = -INFINITY;
		
	Direction dirs[DIR_END];
	for(int i = 0; i < DIR_END; ++i)
		dirs[i] = i;
	std::random_shuffle(dirs, dirs + DIR_END);
	
	for(int i = 0; i < DIR_END; ++i)
	{
		Direction direction = dirs[i];
		
		if(!state.canMove(direction))
			continue;
		
		GameState currentState = state;
		currentState.move(direction);

		double value = heuristic_(currentState, 0);
		if(value > bestValue || bestMove == DIR_END)
		{
			bestMove = direction;
			bestValue = value;
		}
	}
	
#ifdef DEBUG
	moveSequence.clear();
	moveSequence.push_front(bestMove);
#endif
	
	return bestMove;
}
	
} }