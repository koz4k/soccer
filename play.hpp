#include "PlayerVsAi.h"
#include "soccer/ai/Negamax.h"
#include "soccer/ai/RandomHeuristicSearch.h"
#include "soccer/ai/heur/naive.h"
#include "soccer/ai/heur/smartUniform.h"
#include "soccer/ai/heur/uniform.h"

GUI_APP_MAIN
{
	soccer::Ai* ai = new soccer::ai::Negamax(soccer::ai::heur::naive2, 8);
	PlayerVsAi(ai).Run();
}