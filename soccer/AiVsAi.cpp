#include "AiVsAi.h"

using namespace soccer;
using namespace Upp;

AiVsAi::AiVsAi(std::string ai1Name, Ai* ai1, std::string ai2Name, Ai* ai2,
			   int boardWidth, int boardHeight):
	judge_(ai1, ai2, boardWidth, boardHeight)
{
	aiNames_[0] = std::move(ai1Name);
	aiNames_[1] = std::move(ai2Name);
	window_.board.Initialize(Upp::Size(boardWidth, boardHeight));
	window_.board.Freeze();
	
	window_.whoseTurn.SetLabel(aiNames_[0].c_str());
}

void AiVsAi::Run()
{
	window_.Open();
	
	GameState& state = window_.board.GetGameState();
	while(!state.isGameOver())
	{
		window_.whoseTurn.SetLabel(aiNames_[state.whoseTurn() == PLAYER_2].c_str());
		window_.Refresh();
		window_.ProcessEvents();
		
		state = judge_.oneMove();
		Sleep(300);
	}
	
	PromptOK("Wygrał " + String(state.whoWon() == PLAYER_1 ? aiNames_[0] : state.whoWon() == PLAYER_2 ? aiNames_[1] : "nikt"));
	
	window_.Run();
}