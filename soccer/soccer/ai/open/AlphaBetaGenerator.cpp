#ifndef DEBUG

#include "AlphaBetaGenerator.h"
#include "../../GameState.h"
#include <cmath>
#include <limits>

namespace soccer { namespace ai { namespace open {
	
AlphaBetaGenerator::AlphaBetaGenerator(int depth, int limit, Heuristic heuristic):
	depth_(depth), limit_(limit), confidence_(std::numeric_limits<double>::infinity())
{
	ai_ = new AlphaBeta(heuristic, depth_);
}

AlphaBetaGenerator::~AlphaBetaGenerator()
{
	delete ai_;
}

Move* AlphaBetaGenerator::generate(bool meFirst, double confidence)
{
	confidence_ = confidence;
	
	GameState state;
	return meFirst ? (Move*) generateMyMove_(state, limit_) :
					 (Move*) generateYourMove_(state, limit_);
}

MyMove* AlphaBetaGenerator::generateMyMove_(GameState& state, int depth)
{
	if(state.isGameOver() || depth <= 0)
		return nullptr;
	
	Player me = state.whoseTurn();
	Direction direction = ai_->move(state, 0);
	
	if(!state.canMove(direction))
		return nullptr;
	
	state.move(direction);
	Move* nextMove = nullptr;
	if(state.whoseTurn() == me)
		nextMove = generateMyMove_(state, depth);
	else if(ai_->getConfidence() < confidence_)
		nextMove = generateYourMove_(state, depth);
	state.undo(direction);
	return new MyMove(direction, nextMove);
}

YourMove* AlphaBetaGenerator::generateYourMove_(GameState& state, int depth)
{
	if(state.isGameOver() || depth <= 0)
		return nullptr;
	
	Player you = state.whoseTurn();
	YourMove* move = new YourMove();
	bool plug = true;
	for(Direction direction = 0; direction < DIR_END; ++direction)
	{
		if(!state.canMove(direction))
			continue;
		
		state.move(direction);
		Move* nextMove = state.whoseTurn() == you ?
						 (Move*) generateYourMove_(state, depth - 1) :
						 (Move*) generateMyMove_(state, depth - 1);
		if(nextMove)
			plug = false;
		move->setMove(direction, nextMove);
		state.undo(direction);
	}
	
	if(!plug)
		return move;
	else
	{
		delete move;
		return nullptr;
	}
}
	
} } }

#endif
