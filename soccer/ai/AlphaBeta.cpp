#include "AlphaBeta.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>

namespace soccer { namespace ai {

AlphaBeta::AlphaBeta(Heuristic heuristic, int maxDepth):
	HeuristicSearch(std::move(heuristic)), maxDepth_(maxDepth)
{
}

Direction AlphaBeta::move(const GameState& state, int ms
#ifdef DEBUG
		, std::list<Direction>& moveSequence
#endif
	)
{
	GameState stateCopy = state;
	Direction move = DIR_END;
	alphaBeta_(stateCopy, 1, maxDepth_, -INFINITY, INFINITY, move
#ifdef DEBUG
			 , moveSequence
#endif

			);

	return move;
}

double AlphaBeta::alphaBeta_(GameState& state, int color, int depth,
						   	 double alpha, double beta, Direction& move
#ifdef DEBUG
						 , std::list<Direction>& sequence
#endif
						)
{
	if(state.isGameOver() || !depth)
		return heuristic_(state, 0) * color;

	double bestValue = -INFINITY;
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
		double na = alpha, nb = beta;
		if(flip == -1)
			std::swap(na, nb);
		double value = flip * alphaBeta_(state, flip * color, depth - 1, flip * na, flip * nb, dir
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

			alpha = std::max(value, alpha);
			if(alpha >= beta)
				break;
		}
	}

#ifdef DEBUG
		sequence.splice(sequence.end(), bestSequence);
#endif

	return bestValue;
}

} }