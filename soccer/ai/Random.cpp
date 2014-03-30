#include "Random.h"
#include <vector>
#include <cstdlib>
#include <ctime>

namespace soccer { namespace ai {

Random::Random()
{
	srand(time(NULL));
}

Direction Random::move(const GameState& state, int)
{
	Direction direction;
	do
	{
		direction = rand() % DIR_END;
	}
	while(!state.canMove(direction));
	return direction;
}
	
} }
