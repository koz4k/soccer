#ifndef DEBUG

#include "AlphaBetaGenerator.h"
#include "../../GameState.h"
#include <cmath>
#include <limits>

namespace soccer { namespace ai { namespace open {
	
AlphaBetaGenerator::AlphaBetaGenerator(int depth, int limit, Heuristic heuristic):
	ai_(std::make_unique<AlphaBeta>(heuristic, depth_)), depth_(depth), limit_(limit), confidence_(std::numeric_limits<double>::infinity())
{
}

std::unique_ptr<Move> AlphaBetaGenerator::generate(bool meFirst, double confidence)
{
	confidence_ = confidence;
	
	GameState state;
	return meFirst ? generateMyMove_(state, limit_) :
					 generateYourMove_(state, limit_);
}

std::unique_ptr<Move> AlphaBetaGenerator::generateMyMove_(GameState& state, int depth)
{
	if(state.isGameOver() || depth <= 0)
		return nullptr;
	
	Player me = state.whoseTurn();
	Direction direction = ai_->move(state, 0);
	
	if(!state.canMove(direction))
		return nullptr;
	
	state.move(direction);
    std::unique_ptr<Move> nextMove;
	if(state.whoseTurn() == me)
		nextMove = generateMyMove_(state, depth);
	else if(ai_->getConfidence() < confidence_)
		nextMove = generateYourMove_(state, depth);
	state.undo(direction);
	return std::make_unique<MyMove>(direction, std::move(nextMove));
}

std::unique_ptr<Move> AlphaBetaGenerator::generateYourMove_(GameState& state, int depth)
{
	if(state.isGameOver() || depth <= 0)
		return nullptr;
	
	Player you = state.whoseTurn();
    auto move = std::make_unique<YourMove>();
	bool plug = true;
	for(Direction direction = 0; direction < DIR_END; ++direction)
	{
		if(!state.canMove(direction))
			continue;
		
		state.move(direction);
        std::unique_ptr<Move> nextMove = state.whoseTurn() == you ?
						                 generateYourMove_(state, depth - 1) :
						                 generateMyMove_(state, depth - 1);
		if(nextMove)
			plug = false;
		move->setMove(direction, std::move(nextMove));
		state.undo(direction);
	}
	
	if(!plug)
		return move;
	else
		return nullptr;
}
	
} } }

#endif
