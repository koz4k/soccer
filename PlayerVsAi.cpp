#include "PlayerVsAi.h"

using namespace soccer;
using namespace Upp;

PlayerVsAi::PlayerVsAi(Ai* ai, int boardWidth, int boardHeight):
	ai_(ai), finished_(false)
{
	window_.board.Initialize(Size(boardWidth, boardHeight));

	window_.board.WhenMove = THISBACK(WhenMove_);
	window_.board.WhenFullMove = THISBACK(WhenFullMove_);
	window_.board.WhenGameOver = THISBACK(WhenGameOver_);
	
	window_.whoseTurn.SetLabel("Gracz");
}

PlayerVsAi::~PlayerVsAi()
{
	delete ai_;
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

void PlayerVsAi::WhenMove_(const GameState& state, Direction direction)
{
	ai_->opponentMoved(direction);
}

void PlayerVsAi::WhenFullMove_(GameState& state)
{
	window_.whoseTurn.SetLabel(GetPlayerIndicator(state.whoseTurn()));
	window_.ProcessEvents();
	
	while(state.whoseTurn() == PLAYER_2 && !state.isGameOver())
	{
		window_.Refresh();
		window_.ProcessEvents();
		
#ifndef DEBUG
		Direction direction = ai_->move(state, 20000);
#else
		std::list<Direction> moveSequence;
		Direction direction = ai_->move(state, 20000, moveSequence);
		
		window_.board.ClearDebug();
		GameState stateCopy = state;
		soccer::Vector2 p1 = state.getCurrentPosition();
		for(Direction dir : moveSequence)
		{
			soccer::Vector2 p2 = p1.getNeighbor(dir);
			window_.board.AddDebugLine(p1, p2, stateCopy.whoseTurn() == PLAYER_1 ?
											   Upp::Blue() : Upp::Red());
			stateCopy.move(dir);
			p1 = p2;
		}
#endif
	
	
		if(state.canMove(direction))
			state.move(direction);
		else
			PromptOK("nieprawidłowy ruch: " + FormatInt(direction));

		Sleep(300);
	}
	
	window_.whoseTurn.SetLabel(GetPlayerIndicator(state.whoseTurn()));
}

void PlayerVsAi::WhenGameOver_(const GameState& state)
{
	PromptOK(state.whoWon() == PLAYER_1 ? "Wygrałeś!" : "Przegrałeś!");
}