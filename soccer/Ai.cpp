#include "Ai.h"

namespace soccer {
	
Ai::Ai():
	confidence_(0)
{
}
	
Ai::~Ai()
{
}

#ifdef DEBUG

Direction Ai::move(GameState& state, int ms)
{
	std::list<Direction> moveSequence;
	return move(state, ms, moveSequence);
}

#endif

void Ai::opponentMoved(Direction direction)
{
}

void Ai::reset()
{
}

double Ai::getConfidence() const
{
	return confidence_;
}
	
}