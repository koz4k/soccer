#include "RandomHeuristicSearch.h"
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>

namespace soccer { namespace ai {

RandomHeuristicSearch::RandomHeuristicSearch(Heuristic heuristic, double lambda):
	HeuristicSearch(std::move(heuristic)), lambda_(lambda)
{
	srand(time(NULL));
}

Direction RandomHeuristicSearch::move(const GameState& state, int ms
#ifdef DEBUG
								      , std::list<Direction>& moveSequence
#endif
  								     )
{
	Direction dirs[DIR_END];
	for(int i = 0; i < DIR_END; ++i)
		dirs[i] = i;
	std::random_shuffle(dirs, dirs + DIR_END);
	
	Direction move = DIR_END;
	GameState stateCopy = state;
	double cumProbs[DIR_END];
	double cumProb = 0;
	for(int i = 0; i < DIR_END && move == DIR_END; ++i)
	{
		double prob = 0;
		if(stateCopy.canMove(dirs[i]))
		{
			stateCopy.move(dirs[i]);
			prob = exp(lambda_ * heuristic_(stateCopy, 0));
			stateCopy.undo(dirs[i]);
		}

		if(prob == INFINITY)
		{
			move = dirs[i];
			break;
		}
		
		cumProbs[i] = cumProb += prob;
	}
	
	if(move == DIR_END)
	{
		double r = rand();
		double shot = r / RAND_MAX * cumProbs[DIR_END - 1];
		int i = std::lower_bound(cumProbs, cumProbs + DIR_END, shot) - cumProbs;
		move = dirs[i];
	}
	
#ifdef DEBUG
	moveSequence.clear();
	moveSequence.push_front(move);
#endif
	
	return move;
}
	
} }