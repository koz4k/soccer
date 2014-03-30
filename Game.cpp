#include "Game.h"

using namespace Upp;

Game::Game(soccer::Ai* ai, int boardWidth, int boardHeight, bool playerDown):
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

void Game::WhenMove_(const soccer::GameState& state, soccer::Direction)
{
	if(finished_)
		return;
	
	soccer::Point point = state.getCurrentPosition();
	if(point.y == aiGate_)
		Won_();
	else if(point.y == playerGate_)
		Lost_();
	
	if(state.isBlocked())
		Lost_();
}

void Game::WhenFullMove_(soccer::GameState& state)
{	
	if(finished_)
		return;

	window_.board.Freeze();
	
	do
	{
		soccer::Direction direction = ai_->move(state, 0);
		state.move(direction);
	}
	while(state.canRebound() && !state.isBlocked());
	
	if(state.isBlocked())
		Won_();
	
	window_.board.Unfreeze();
}

void Game::Won_()
{
	PromptOK("Wygrales!");
	finished_ = true;
	window_.board.Freeze();
}

void Game::Lost_()
{
	PromptOK("Przegrales!");
	finished_ = true;
	window_.board.Freeze();
}
