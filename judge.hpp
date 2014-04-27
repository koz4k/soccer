#include "AiVsAi.h"
#include "soccer/ai/Negamax.h"
#include "soccer/ai/heur/naive.h"

GUI_APP_MAIN
{
	soccer::ai::Negamax ai1(soccer::ai::heur::naive1, 7);
	soccer::ai::Negamax ai2(soccer::ai::heur::naive2, 8);
	AiVsAi("negamax6", ai1, "negamax7", ai2).Run();
}