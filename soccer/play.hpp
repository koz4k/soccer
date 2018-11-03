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
	auto ai = std::make_unique<MonteCarloTreeSearch>(std::make_unique<RouletteSearch>(naive1, 1),
                  		  			  std::make_unique<RouletteSearch>(naive2, 1),
                  		  			  1, 1, naive1, 0.0, 0.0, 10000.0,
                  		  			  std::make_unique<timing::Uniform>(3.0, 30), 0);
	PlayerVsAi(std::move(ai)).Run();
}
