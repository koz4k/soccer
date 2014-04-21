#include "Negamax.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>

namespace soccer { namespace ai {

Negamax::Negamax(Heuristic heuristic, int maxDepth):
	HeuristicSearch(heuristic), maxDepth_(maxDepth)
{
	srand(time(NULL));
}

Direction Negamax::move(const GameState& state, int ms)
{
	if(queue_.empty())
	{
		GameState stateCopy = state;
		negamax_(stateCopy, queue_, true, 1, maxDepth_);
	}
	
	Direction direction = queue_.front();
	queue_.pop_front();
	return direction;
}

double Negamax::negamax_(GameState& state, std::list<Direction>& sequence,
						 bool saveSequence, int color, int depth)
{
	if(state.isGameOver() || !depth)
		return heuristic_(state, 0) * color;
	
	double bestValue = -INFINITY;
	std::list<Direction> bestSequence;
	
	Direction dirs[DIR_END];
	for(int i = 0; i < DIR_END; ++i)
		dirs[i] = i;
	std::random_shuffle(dirs, dirs + DIR_END);
	
	for(int i = 0; i < DIR_END; ++i)
	{
		Direction direction = dirs[i];
		
		if(!state.canMove(direction))
			continue;
		
		std::list<Direction> temp;
		temp.push_back(direction);
		
		state.move(direction);
		double value = 0;
		if(state.canRebound())
			value = std::max(negamax_(state, temp, saveSequence, color, depth - 1), bestValue);
		else
			value = std::max(-negamax_(state, temp, false, -color, depth - 1), bestValue);
		state.undo(direction);
		
		if(value > bestValue || bestSequence.empty())
		{
			bestValue = value;
			bestSequence = std::move(temp);
		}
	}
	
	if(saveSequence)
		sequence.splice(sequence.end(), bestSequence);
	
	return bestValue;
}
	
} }
