#include "Greedy.h"
#include <algorithm>

namespace soccer { namespace ai {

Greedy::Greedy(Heuristic heuristic):
	HeuristicSearch(heuristic)
{
	srand(time(NULL));
}

Direction Greedy::move(const GameState& state, int ms)
{
	Direction bestMove = DIR_END;
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
		double value = heuristic_(currentState);
		if(value > bestValue || bestMove == DIR_END)
		{
			bestMove = direction;
			bestValue = value;
		}
	}
	
	return bestMove;
}
	
} }
