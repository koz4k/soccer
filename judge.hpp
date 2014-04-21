#include "AiVsAi.h"
#include "soccer/ai/ShallowHeuristicSearch.h"
#include "soccer/ai/Negamax.h"
#include "soccer/ai/heur/Negamax.h"
#include "soccer/ai/heur/naive.h"

GUI_APP_MAIN
{
	soccer::ai::ShallowHeuristicSearch ai1(soccer::ai::heur::Negamax(soccer::ai::heur::naive1, 7));
	soccer::ai::Negamax ai2(soccer::ai::heur::naive2, 8);
	AiVsAi("new negamax", ai1, "old negamax", ai2).Run();
}