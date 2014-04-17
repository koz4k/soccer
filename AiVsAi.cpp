#include "AiVsAi.h"

using namespace soccer;
using namespace Upp;

AiVsAi::AiVsAi(const char* ai1Name, Ai* ai1, const char* ai2Name, Ai* ai2,
			   int boardWidth, int boardHeight):
	judge_(ai1, ai2, boardWidth, boardHeight)
{
	aiNames_[0] = ai1Name;
	aiNames_[1] = ai2Name;
	window_.board.Initialize(Upp::Size(boardWidth, boardHeight));
	window_.board.Freeze();
	
	window_.whoseTurn.SetLabel(ai1Name);
}

void AiVsAi::Run()
{
	GameState& state = window_.board.GetGameState();
	while(!state.isGameOver())
	{
		window_.whoseTurn.SetLabel(aiNames_[state.whoseTurn() == PLAYER_2]);
		window_.ProcessEvents();
		
		state = judge_.oneMove();
	}
}