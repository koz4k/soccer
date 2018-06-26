#include "Uniform.h"

namespace soccer { namespace timing {

Uniform::Uniform(double multiplier, int timeMargin, int moveCount):
	TimingStrategy(timeMargin), mul_(multiplier), moveCount_(moveCount), movesLeft_(moveCount)
{
}

void Uniform::setGameState(const GameState& state)
{
	movesLeft_ = moveCount_ - state.whichMove();
}

double Uniform::allocateTime_()
{
	return std::min(mul_ * 2.0 / movesLeft_, 0.5);
}
	
} }