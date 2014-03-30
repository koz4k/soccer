#include "Game.h"

using namespace soccer;
using namespace Upp;

// TODO: wywalic wiekszosc logiki do Board

Game::Game(Ai* ai, int boardWidth, int boardHeight, bool playerDown):
	ai_(ai), finished_(false)
{
	window_.board.SetBoardSize(Size(boardWidth, boardHeight));
	
	playerGate_ = (playerDown ? -1 : 1) * (boardHeight / 2 + 1);
	aiGate_ = -playerGate_;

	window_.board.WhenMove = THISBACK(WhenMove_);
	window_.board.WhenFullMove = THISBACK(WhenFullMove_);
}

void Game::Run()
{
	window_.Run();
}

void Game::WhenMove_(const GameState& state, Direction)
{
	if(finished_)
		return;
	
	Vector2 position = state.getCurrentPosition();
	if(position.y == aiGate_)
		Won_();
	else if(position.y == playerGate_ || state.isBlocked())
		Lost_();
}

void Game::WhenFullMove_(GameState& state)
{	
	if(finished_)
		return;

	window_.board.Freeze();
	
	do
	{
		Direction direction = ai_->move(state, 0);
		state.move(direction);
	}
	while(state.canRebound() && !state.isBlocked() &&
		  std::abs(state.getCurrentPosition().y) != std::abs(playerGate_));
	
	window_.board.Unfreeze();
	
	if(state.getCurrentPosition().y == playerGate_)
		Lost_();
	else if(state.isBlocked())
		Won_();
}

void Game::Won_()
{
	PromptOK("Wygrałeś!");
	finished_ = true;
	window_.board.Freeze();
}

void Game::Lost_()
{
	PromptOK("Przegrałeś!");
	finished_ = true;
	window_.board.Freeze();
}
