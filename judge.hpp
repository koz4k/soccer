#include "AiVsAi.h"
#include "soccer/ai/Negamax.h"
#include "soccer/ai/heur/naive.h"

GUI_APP_MAIN
{
	soccer::Ai* ai1 = new soccer::ai::Negamax(soccer::ai::heur::naive1, 7);
	soccer::Ai* ai2 = new soccer::ai::Negamax(soccer::ai::heur::naive2, 8);
	AiVsAi("negamax7", ai1, "negamax8", ai2).Run();
}