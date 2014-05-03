#include "PlayerVsAi.h"
#include "soccer/ai/MonteCarloTreeSearch.h"
#include "soccer/ai/AlphaBeta.h"
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
	//Ai* ai = new MonteCarloTreeSearch(new RandomHeuristicSearch(naive1, 1.6),
	//                                  new RandomHeuristicSearch(naive2, 1.6), 10000, 5, 1.4);
	//Ai* ai = new Negamax(naive2, 8);
	Ai* ai = new AlphaBeta(naive2, 12);
	PlayerVsAi(ai).Run();
}