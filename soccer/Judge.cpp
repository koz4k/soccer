#include "Judge.h"

namespace soccer {

Judge::Judge(Ai& player1, Ai& player2, int boardWidth, int boardHeight):
	player1_(player1), player2_(player2),
	state_(boardWidth, boardHeight)
{
	currentPlayer_ = &player1_;
}

const GameState& Judge::getGameState() const
{
	return state_;
}

const GameState& Judge::oneMove() // TODO: obsluga bledow, czas
{
	Direction direction = currentPlayer_->move(state_, 0);
	if(state_.canMove(direction))
		state_.move(direction);
	currentPlayer_ = state_.whoseTurn() == PLAYER_1 ? &player1_ : &player2_;
	return state_;
}

GameState Judge::run()
{
	while(!state_.isGameOver())
		oneMove();
	
	GameState copy = state_;
	state_ = GameState();
	
	return copy;
}
	
}