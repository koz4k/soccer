#include "Negamax.h"
#include <algorithm>

#include <CtrlLib/CtrlLib.h>

namespace soccer { namespace ai {

Negamax::Negamax(Heuristic heuristic, int maxDepth):
	HeuristicSearch(heuristic), maxDepth_(maxDepth)
{
}

Direction Negamax::move(const GameState& state, int ms)
{
	if(queue_.empty())
	{
		GameState stateCopy = state;
		negamax_(stateCopy, queue_, true, 1, maxDepth_);
	}
	
	using namespace Upp;
	//PromptOK("moves planned: " + FormatInt(queue_.size()) + ", first move: " + FormatInt(queue_.front()));

	Direction direction = queue_.front();
	queue_.pop_front();
	return direction;
}

double Negamax::negamax_(GameState& state, std::list<Direction>& sequence,
						 bool saveSequence, int color, int depth)
{
	if(state.isGameOver() || !depth)
		return heuristic_(state) * color;
	
	double bestValue = -INFINITY;
	std::list<Direction> bestSequence;
	for(int direction = DIR_BEGIN; direction < DIR_END; ++direction)
	{
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
		
		if(value > bestValue)
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
