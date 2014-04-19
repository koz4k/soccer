#include "PlayerVsAi.h"
#include "soccer/ai/Negamax.h"

double naiveHeuristic(const soccer::GameState& state)
{
	soccer::Vector2 position = state.getCurrentPosition();
	
	if(state.isGameOver())
		return position.y == -6 ? INFINITY : -INFINITY;
	
	return std::max(6 - position.y, -std::abs(position.x)) -
		   std::max(6 + position.y, -std::abs(position.x));
}

GUI_APP_MAIN
{
	soccer::ai::Negamax ai(naiveHeuristic, 8);
	PlayerVsAi(&ai).Run();
}
