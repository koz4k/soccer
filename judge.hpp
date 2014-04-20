#include "AiVsAi.h"
#include "soccer/ai/Negamax.h"

double naiveHeuristic1(const soccer::GameState& state)
{
	soccer::Vector2 position = state.getCurrentPosition();
	
	if(state.isGameOver())
		return position.y == 6 ? INFINITY : -INFINITY;
	
	return std::max(6 + position.y, -std::abs(position.x)) -
		   std::max(6 - position.y, -std::abs(position.x));
}

double naiveHeuristic2(const soccer::GameState& state)
{
	soccer::Vector2 position = state.getCurrentPosition();
	
	if(state.isGameOver())
		return position.y == -6 ? INFINITY : -INFINITY;
	
	return std::max(6 - position.y, -std::abs(position.x)) -
		   std::max(6 + position.y, -std::abs(position.x));
}

GUI_APP_MAIN
{
	soccer::ai::Negamax ai1(naiveHeuristic1, 7);
	soccer::ai::Negamax ai2(naiveHeuristic2, 6);
	AiVsAi("negamax 7", ai1, "negamax 6", ai2).Run();
}