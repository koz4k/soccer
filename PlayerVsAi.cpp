#include "PlayerVsAi.h"

using namespace soccer;
using namespace Upp;

PlayerVsAi::PlayerVsAi(Ai* ai, int boardWidth, int boardHeight):
	ai_(ai), finished_(false)
{
	window_.board.Initialize(Size(boardWidth, boardHeight));

	window_.board.WhenFullMove = THISBACK(WhenFullMove_);
	window_.board.WhenGameOver = THISBACK(WhenGameOver_);
	
	window_.whoseTurn.SetLabel("Gracz");
}

void PlayerVsAi::Run()
{
	window_.Run();
}

const char* GetPlayerIndicator(Player player)
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

void PlayerVsAi::WhenFullMove_(GameState& state)
{
	window_.whoseTurn.SetLabel(GetPlayerIndicator(state.whoseTurn()));
	window_.ProcessEvents();
	
	while(state.whoseTurn() == PLAYER_2 && !state.isGameOver())
	{
		Direction direction = ai_->move(state, 0);
		state.move(direction);
	}
	
	window_.whoseTurn.SetLabel(GetPlayerIndicator(state.whoseTurn()));
}

void PlayerVsAi::WhenGameOver_(const GameState& state)
{
	PromptOK(state.whoWon() == PLAYER_1 ? "Wygrałeś!" : "Przegrałeś!");
}
