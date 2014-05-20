#include "Judge.h"
#include "Timer.h"

namespace soccer {

Judge::Judge(Ai* player1, Ai* player2, int matchTime, int boardWidth, int boardHeight):
	player1_(player1), player2_(player2), matchTime_(matchTime),
	time1_(matchTime), time2_(matchTime), state_(boardWidth, boardHeight)
{
}

Judge::Judge(Ai* player1, Ai* player2, GameState state, int matchTime):
	player1_(player1), player2_(player2), matchTime_(matchTime),
	time1_(matchTime), time2_(matchTime), state_(std::move(state))
{
}

const GameState& Judge::getGameState() const
{
	return state_;
}

const GameState& Judge::oneMove() // TODO: obsluga bledow, czas
{
	Ai* currentPlayer = state_.whoseTurn() == PLAYER_1 ? player1_ : player2_;
	int& timeLeft = state_.whoseTurn() == PLAYER_1 ? time1_ : time2_;

	Timer timer(timeLeft);
	Direction direction = currentPlayer->move(state_, timeLeft);
	timeLeft = timer();
	
	if(state_.canMove(direction))
	{
		(state_.whoseTurn() == PLAYER_2 ? player1_ : player2_)->opponentMoved(direction);
		state_.move(direction);
	}
	return state_;
}

GameState Judge::run()
{
	reset();
	
	while(!state_.isGameOver())
		oneMove();
	
	GameState state;
	std::swap(state, state_);
	
	return state;
}

void Judge::reset()
{
	player1_->reset();
	player2_->reset();
	
	time1_ = time2_ = matchTime_;
}

}