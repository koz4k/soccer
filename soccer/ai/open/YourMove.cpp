#include "YourMove.h"

namespace soccer { namespace ai { namespace open {

YourMove::YourMove()
{
	for(int i = 0; i < DIR_END; ++i)
		moves_[i] = nullptr;
}

YourMove::~YourMove()
{
	for(int i = 0; i < DIR_END; ++i)
		delete moves_[i];
}

bool YourMove::isMyTurn() const
{
	return false;
}

void YourMove::setMove(Direction direction, const Move* move)
{
	delete moves_[direction];
	moves_[direction] = move;
}

const Move* YourMove::advance(Direction direction) const
{
	return moves_[direction];
}
	
} } }