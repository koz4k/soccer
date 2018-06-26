#include "PlayerVsAi.h"
#include "soccer/ai/MonteCarloTreeSearch.h"
#include "soccer/ai/AlphaBeta.h"
#include "soccer/ai/Negamax.h"
#include "soccer/ai/MaxSearch.h"
#include "soccer/ai/MaxOfFewSearch.h"
#include "soccer/ai/DeepMaxOfFewSearch.h"
#include "soccer/ai/RouletteSearch.h"
#include "soccer/ai/WithOpenings.h"
#include "soccer/ai/heur/SimpleMonteCarlo.h"
#include "soccer/ai/heur/ReboundAwareNaive.h"
#include "soccer/ai/heur/naive.h"
#include "soccer/ai/heur/smartUniform.h"
#include "soccer/ai/heur/uniform.h"
#include "soccer/timing/Uniform.h"

using namespace soccer;
using namespace ai;
using namespace heur;

GUI_APP_MAIN
{
	//Ai* ai = new MonteCarloTreeSearch(new MaxOfFewSearch(naive1, 1),
	//                                  new MaxOfFewSearch(naive2, 1), 1000, 1, 0.5);
	//Ai* ai = new WithOpenings("op1-19-17-1-2-1-khaki15", "op2-19-17-1-2-1-khaki15", new AlphaBeta(naive2, 12));
	/*Ai* ai = new MonteCarloTreeSearch(new RouletteSearch(ReboundAwareNaive(10.0, PLAYER_1), 1.6),
                 		  			  new RouletteSearch(ReboundAwareNaive(10.0, PLAYER_2), 1.6),
                  		  			  1, 0.5, ReboundAwareNaive(36.0, PLAYER_2), 0.02, 0.3, 1e9,
                  		  			  new timing::Uniform(5.0, 2));*/
	//Ai* ai = new DeepMaxOfFewSearch(naive2, 1024);
	Ai* ai = new MonteCarloTreeSearch(new RouletteSearch(naive1, 1),
                  		  			  new RouletteSearch(naive2, 1),
                  		  			  1, 1, naive1, 0.0, 0.0, 10000.0,
                  		  			  new timing::Uniform(3.0, 30), 0);
	PlayerVsAi(ai).Run();
}