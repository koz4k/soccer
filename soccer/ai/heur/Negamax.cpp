#include "Negamax.h"
#include <algorithm>

namespace soccer { namespace ai { namespace heur {
	
Negamax::Negamax(Heuristic heuristic, int maxDepth):
	heuristic_(heuristic), maxDepth_(maxDepth)
{
}

double Negamax::negamax_(GameState& state, int color, int depth)
{	
	if(state.isGameOver() || !depth)
		return heuristic_(state, 0) * color;
	
	double bestValue = -INFINITY;
	Direction bestMove = DIR_END;
	
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
		double value = 0;
		if(state.canRebound())
			value = std::max(negamax_(state, color, depth - 1), bestValue);
		else
			value = std::max(-negamax_(state, -color, depth - 1), bestValue);
		state.undo(direction);
		
		if(value > bestValue || bestMove == DIR_END)
		{
			bestValue = value;
			bestMove = direction;
		}
	}
	
	return bestValue;
}

#include <cstdio>

double Negamax::operator()(const GameState& state, int ms)
{
	if(state.isGameOver())
		return heuristic_(state, 0);
		
	GameState stateCopy = state;
	double val = 0;
	if(state.canRebound())
		val = negamax_(stateCopy, 1, maxDepth_);
	else
		val = -negamax_(stateCopy, -1, maxDepth_);
	
//printf("%f\n", val);
//fflush(stdout);

	return val;
}
	
} } }