#include "WithOpenings.h"
#include "open/MyMove.h"
#include "open/YourMove.h"
#include "open/io.h"
#include <cassert>

namespace soccer { namespace ai {

using namespace open;

WithOpenings::WithOpenings(const std::string& file1, const std::string& file2, std::unique_ptr<Ai> mainAi):
	move1_(open::load(file1)), move2_(open::load(file2)), mainAi_(std::move(mainAi)), initialized_(false)
{
}

Direction WithOpenings::move(GameState& state, int ms
#ifdef DEBUG
							 , std::list<Direction>& moveSequence
#endif
							)
{
	if(!initialized_)
	{
		move_ = std::move(move1_);
		initialized_ = true;
	}
	
	Direction move = DIR_END;
	if(move_)
	{
		assert(move_->isMyTurn());
        MyMove* myMove = (MyMove*) move_.get();
		move = myMove->getDirection();
		move_ = std::move(myMove->advance());
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
		move_ = std::move(move2_);
		initialized_ = true;
	}
	
	if(move_)
	{
		assert(!move_->isMyTurn());
		move_ = ((YourMove*) move_.get())->advance(direction);
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
