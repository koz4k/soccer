#include "Greedy.h"
#include <algorithm>

namespace soccer { namespace ai {

Greedy::Greedy(Heuristic heuristic):
	HeuristicSearch(heuristic)
{
}

Direction Greedy::move(const GameState& state, int ms)
{
	Direction bestMove = DIR_END;
	double bestValue = -INFINITY;
	for(int direction = 0; direction < DIR_END; ++direction)
	{
		if(!state.canMove(direction))
			continue;
		
		GameState currentState = state;
		currentState.move(direction);
		double value = heuristic_(currentState);
		if(value > bestValue)
		{
			bestMove = direction;
			bestValue = value;
		}
	}
	
	return bestMove;
}
	
} }
