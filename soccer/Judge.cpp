#include "Judge.h"

namespace soccer {

Judge::Judge(Ai* player1, Ai* player2, int boardWidth, int boardHeight):
	player1_(player1), player2_(player2), state_(boardWidth, boardHeight)
{
}

Judge::Judge(Ai* player1, Ai* player2, GameState state):
	player1_(player1), player2_(player2), state_(std::move(state))
{
}

const GameState& Judge::getGameState() const
{
	return state_;
}

const GameState& Judge::oneMove() // TODO: obsluga bledow, czas
{
	Ai* currentPlayer = state_.whoseTurn() == PLAYER_1 ? player1_ : player2_;
	Direction direction = currentPlayer->move(state_, 0);
	if(state_.canMove(direction))
		state_.move(direction);
	return state_;
}

GameState Judge::run()
{
	while(!state_.isGameOver())
		oneMove();
	
	GameState state = std::move(state_);
	state_ = GameState();
	
	return state;
}
	
}