#include "Game.h"

using namespace soccer;
using namespace Upp;

Game::Game(Ai* ai, int boardWidth, int boardHeight, bool playerDown):
	ai_(ai), finished_(false)
{
	window_.board.Initialize(Size(boardWidth, boardHeight), playerDown);
	
	playerGate_ = (playerDown ? -1 : 1) * (boardHeight / 2 + 1);
	aiGate_ = -playerGate_;

	window_.board.WhenFullMove = THISBACK(WhenFullMove_);
	window_.board.WhenGameOver = THISBACK(WhenGameOver_);
}

void Game::Run()
{
	window_.Run();
}

void Game::WhenFullMove_(GameState& state)
{
	do
	{
		Direction direction = ai_->move(state, 0);
		state.move(direction);
	}
	while(state.canRebound() && !state.isBlocked() &&
		  std::abs(state.getCurrentPosition().y) != std::abs(playerGate_));
}

void Game::WhenGameOver_(const GameState& state, bool won)
{
	PromptOK(won ? "Wygrałeś!" : "Przegrałeś!");
}
