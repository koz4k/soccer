#include "AiVsAi.h"
#include "soccer/ai/Negamax.h"
#include "soccer/ai/MonteCarloTreeSearch.h"
#include "soccer/ai/RouletteSearch.h"
#include "soccer/ai/heur/naive.h"

using namespace soccer;
using namespace ai;
using namespace heur;

GUI_APP_MAIN
{
	Ai* ai1 = new MonteCarloTreeSearch(new RouletteSearch(naive1, 1.8),
	                                   new RouletteSearch(naive2, 1.8), 10000, 5, 1.6);
	Ai* ai2 = new MonteCarloTreeSearch(new RouletteSearch(naive1, 1.8),
	                                   new RouletteSearch(naive2, 1.8), 10000, 1, 1.6);
	AiVsAi("monte carlo 5", ai1, "monte carlo 1", ai2).Run();
}