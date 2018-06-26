#include "MyMove.h"

namespace soccer { namespace ai { namespace open {

MyMove::MyMove(Direction direction, const Move* move):
	direction_(direction), move_(move)
{
}

MyMove::~MyMove()
{
	delete move_;
}

bool MyMove::isMyTurn() const
{
	return true;
}

Direction MyMove::getDirection() const
{
	return direction_;
}

const Move* MyMove::advance() const
{
	return move_;
}

} } }