#include "PlayerVsAi.h"
#include "soccer/ai/Negamax.h"
#include "soccer/ai/heur/naive.h"

GUI_APP_MAIN
{
	soccer::ai::Negamax ai(soccer::ai::heur::naive2, 8);
	PlayerVsAi(ai).Run();
}