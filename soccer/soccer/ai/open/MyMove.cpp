#include "MyMove.h"

namespace soccer { namespace ai { namespace open {

MyMove::MyMove(Direction direction, std::unique_ptr<Move> move):
	direction_(direction), move_(std::move(move))
{
}

bool MyMove::isMyTurn() const
{
	return true;
}

Direction MyMove::getDirection() const
{
	return direction_;
}

std::unique_ptr<Move> MyMove::advance()
{
	return std::move(move_);
}

} } }
