#include "PlayerVsAi.h"
#include "soccer/ai/Negamax.h"
#include "soccer/ai/Random.h"

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
	//soccer::ai::Random ai;
	soccer::ai::Negamax ai(naiveHeuristic, 9);
	PlayerVsAi(&ai).Run();
}
