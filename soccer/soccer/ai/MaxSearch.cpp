#include "MaxSearch.h"
#include <algorithm>
#include <limits>

namespace soccer { namespace ai {

MaxSearch::MaxSearch(Heuristic heuristic):
	HeuristicSearch(std::move(heuristic))
{
	srand(time(nullptr));
}

Direction MaxSearch::move(GameState& state, int ms
#ifdef DEBUG
						  , std::list<Direction>& moveSequence
#endif
  		                 )
{
	int bestMove = DIR_END;
	double bestValue = -std::numeric_limits<double>::infinity();
		
	Direction dirs[DIR_END];
	for(int i = 0; i < DIR_END; ++i)
		dirs[i] = i;
	std::random_shuffle(dirs, dirs + DIR_END);
	
	for(int i = 0; i < DIR_END; ++i)
	{
		Direction direction = dirs[i];
		
		if(!state.canMove(direction))
			continue;
		
		state.move(direction);
		double value = heuristic_(state);
		state.undo(direction);
		
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
