#include "PlayerVsAi.h"
#include "soccer/ai/ShallowHeuristicSearch.h"
#include "soccer/ai/heur/Negamax.h"
#include "soccer/ai/heur/naive.h"

GUI_APP_MAIN
{
	soccer::ai::ShallowHeuristicSearch ai(soccer::ai::heur::Negamax(soccer::ai::heur::naive2, 6));
	PlayerVsAi(ai).Run();
}