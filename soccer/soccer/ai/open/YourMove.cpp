#include "YourMove.h"

namespace soccer { namespace ai { namespace open {

bool YourMove::isMyTurn() const
{
	return false;
}

void YourMove::setMove(Direction direction, std::unique_ptr<Move> move)
{
	moves_[direction] = std::move(move);
}

std::unique_ptr<Move> YourMove::advance(Direction direction)
{
	return std::move(moves_[direction]);
}
	
} } }
