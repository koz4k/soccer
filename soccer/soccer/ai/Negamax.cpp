#include "Negamax.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <limits>

namespace soccer { namespace ai {

Negamax::Negamax(Heuristic heuristic, int maxDepth):
	HeuristicSearch(std::move(heuristic)), maxDepth_(maxDepth)
{
	srand(time(nullptr));
}

Direction Negamax::move(GameState& state, int ms
#ifdef DEBUG
		, std::list<Direction>& moveSequence
#endif
	)
{
	GameState stateCopy = state;
	Direction move = DIR_END;
	negamax_(stateCopy, 1, maxDepth_, move
#ifdef DEBUG
			 , moveSequence
#endif

			);

	return move;
}

double Negamax::negamax_(GameState& state, int color, int depth, Direction& move
#ifdef DEBUG
						 , std::list<Direction>& sequence
#endif
						)
{
	if(state.isGameOver() || !depth)
		return heuristic_(state) * color;

	double bestValue = -std::numeric_limits<double>::infinity();
	move = DIR_END;
	
#ifdef DEBUG
	std::list<Direction> bestSequence;
#endif

	Direction dirs[DIR_END];
	for(int i = 0; i < DIR_END; ++i)
		dirs[i] = i;
	std::random_shuffle(dirs, dirs + DIR_END);

	for(int i = 0; i < DIR_END; ++i)
	{
		Direction direction = dirs[i];

		if(!state.canMove(direction))
			continue;

#ifdef DEBUG
		std::list<Direction> seq;
		seq.push_back(direction);
#endif

		state.move(direction);
		Direction dir = DIR_END;
		int flip = state.canRebound() ? 1 : -1;
		double value = flip * negamax_(state, flip * color, depth - 1, dir
#ifdef DEBUG
									   , seq
#endif
									  );
		state.undo(direction);

		if(value > bestValue || move == DIR_END)
		{
			bestValue = value;
			move = direction;
#ifdef DEBUG
			bestSequence = std::move(seq);
#endif
		}
	}

#ifdef DEBUG
		sequence.splice(sequence.end(), bestSequence);
#endif

	return bestValue;
}

} }
