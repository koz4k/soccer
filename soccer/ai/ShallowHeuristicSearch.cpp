#include "ShallowHeuristicSearch.h"
#include <algorithm>

namespace soccer { namespace ai {

ShallowHeuristicSearch::ShallowHeuristicSearch(Heuristic heuristic):
	HeuristicSearch(heuristic)
{
}

#include <cstdio>

Direction ShallowHeuristicSearch::move(const GameState& state, int ms)
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
//printf("%d: ", direction);
//fflush(stdout);
		double value = heuristic_(currentState, 0);
		if(value > bestValue || bestMove == DIR_END)
		{
			bestMove = direction;
			bestValue = value;
		}
	}
	
//printf("\n");
	
	return bestMove;
}
	
} }