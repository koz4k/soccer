#ifdef DEBUG

#include "Ai.h"

namespace soccer {

Direction Ai::move(const GameState& state, int ms)
{
	std::list<Direction> moveSequence;
	return move(state, ms, moveSequence);
}
	
}

#endif