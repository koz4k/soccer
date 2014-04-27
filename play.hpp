#include "PlayerVsAi.h"
#include "soccer/ai/Negamax.h"
#include "soccer/ai/RandomHeuristicSearch.h"
#include "soccer/ai/heur/naive.h"
#include "soccer/ai/heur/smartUniform.h"
#include "soccer/ai/heur/uniform.h"

GUI_APP_MAIN
{
	soccer::ai::Negamax ai(soccer::ai::heur::naive2, 8);
	//soccer::ai::RandomHeuristicSearch ai(soccer::ai::heur::naive2, 0.4);
	PlayerVsAi(ai).Run();
}