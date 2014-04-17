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

const char* getPlayerIndicator(Player player)
{
	switch(player)
	{
	  case PLAYER_1:
	  	return "Gracz";
	  
	  case PLAYER_2:
	  	return "Komputer";
	  
	  default:
	  	return "Błąd";
	}
}

void Game::WhenFullMove_(GameState& state)
{
	window_.whoseTurn.SetLabel(getPlayerIndicator(state.whoseTurn()));
	window_.ProcessEvents();
	
	while(state.whoseTurn() == PLAYER_2 && !state.isGameOver())
	{
		Direction direction = ai_->move(state, 0);
		state.move(direction);
	}
	
	window_.whoseTurn.SetLabel(getPlayerIndicator(state.whoseTurn()));
}

void Game::WhenGameOver_(const GameState& state)
{
	PromptOK(state.whoWon() == PLAYER_1 ? "Wygrałeś!" : "Przegrałeś!");
}
