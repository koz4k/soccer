#include "MaxOfFewSearch.h"
#include <cmath>
#include <cstdlib>
#include <ctime>

namespace soccer { namespace ai {

MaxOfFewSearch::MaxOfFewSearch(Heuristic heuristic, int k):
	HeuristicSearch(std::move(heuristic)), k_(k)
{
	srand(time(nullptr));
}

Direction MaxOfFewSearch::move(GameState& state, int ms
#ifdef DEBUG
							   , std::list<Direction>& moveSequence
#endif
  							  )
{
	Direction bestMove = DIR_END;
	double bestValue = -INFINITY;
	for(int i = 0; i < k_ || bestMove == DIR_END; ++i)
	{
		Direction direction = rand() % DIR_END;
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