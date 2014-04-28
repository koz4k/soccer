#include "PlayerVsAi.h"
#include "soccer/ai/Negamax.h"
#include "soccer/ai/MaxHeuristicSearch.h"
#include "soccer/ai/RandomHeuristicSearch.h"
#include "soccer/ai/heur/SimpleMonteCarlo.h"
#include "soccer/ai/heur/naive.h"
#include "soccer/ai/heur/smartUniform.h"
#include "soccer/ai/heur/uniform.h"

using namespace soccer;
using namespace ai;
using namespace heur;

GUI_APP_MAIN
{
	//Ai* ai = new Negamax(naive2, 8);
	Ai* ai = new MaxHeuristicSearch(SimpleMonteCarlo(new Negamax(naive1, 4),
													 new Negamax(naive2, 4),
													 10, PLAYER_2));
	PlayerVsAi(ai).Run();
}