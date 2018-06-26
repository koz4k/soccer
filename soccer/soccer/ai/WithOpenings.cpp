#include "WithOpenings.h"
#include "open/MyMove.h"
#include "open/YourMove.h"
#include "open/io.h"
#include <cassert>

namespace soccer { namespace ai {

using namespace open;

WithOpenings::WithOpenings(const std::string& file1, const std::string& file2, Ai* mainAi):
	move1_(open::load(file1)), move2_(open::load(file2)), move_(nullptr), mainAi_(mainAi), initialized_(false)
{
}

WithOpenings::~WithOpenings()
{
	delete move1_;
	delete move2_;
	delete mainAi_;
}

Direction WithOpenings::move(GameState& state, int ms
#ifdef DEBUG
							 , std::list<Direction>& moveSequence
#endif
							)
{
	if(!initialized_)
	{
		move_ = move1_;
		initialized_ = true;
	}
	
	Direction move = DIR_END;
	if(move_)
	{
		assert(move_->isMyTurn());
		move = ((MyMove*) move_)->getDirection();
		move_ = ((MyMove*) move_)->advance();
	}
	else
		move = mainAi_->move(state, ms
#ifdef DEBUG
							 , moveSequence
#endif
							);
	
	return move;
}

void WithOpenings::opponentMoved(Direction direction)
{
	if(!initialized_)
	{
		move_ = move2_;
		initialized_ = true;
	}
	
	if(move_)
	{
		assert(!move_->isMyTurn());
		move_ = ((YourMove*) move_)->advance(direction);
	}
	else
		mainAi_->opponentMoved(direction);
}

void WithOpenings::reset()
{
	initialized_ = false;
	move_ = nullptr;

	mainAi_->reset();
}
	
} }