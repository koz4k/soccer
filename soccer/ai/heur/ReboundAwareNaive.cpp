#include "ReboundAwareNaive.h"
#include "naive.h"

namespace soccer { namespace ai { namespace heur {
	
ReboundAwareNaive::ReboundAwareNaive(double reboundWeight, Player player):
	r_(reboundWeight), player_(player)
{
}

double ReboundAwareNaive::operator()(const GameState& state)
{
	return (player_ == PLAYER_1 ? naive1(state) : naive2(state)) +
		   r_ * state.canRebound() * (state.whoseTurn() == player_ ? 1 : -1);
}
	
} } }