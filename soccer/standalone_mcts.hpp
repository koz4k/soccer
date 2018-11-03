#define NDEBUG

#include "soccer/ai/MonteCarloTreeSearch.h"
#include "soccer/ai/WithOpenings.h"
#include "soccer/ai/RouletteSearch.h"
#include "soccer/ai/heur/naive.h"
#include "soccer/timing/Uniform.h"
#include "soccer/AiStandalone.h"

using namespace soccer;
using namespace ai;
using namespace heur;

int main()
{
	/*AiStandalone(std::make_unique<MonteCarloTreeSearch>(std::make_unique<RouletteSearch>(ReboundAwareNaive(10.0, PLAYER_1), 1.6),
	                              		  std::make_unique<RouletteSearch>(ReboundAwareNaive(10.0, PLAYER_2), 1.6),
	                              		  1, 0.5, ReboundAwareNaive(36.0, PLAYER_1), 0.02, 0.3, 1e9,
	                              		  std::make_unique<timing::Uniform>(3.0, 3))).run();*/
	                              		  
	AiStandalone(/*std::make_unique<WithOpenings>("pk346962-openings1.dat", "pk346962-openings2.dat",*/ std::make_unique<MonteCarloTreeSearch>(std::make_unique<RouletteSearch>(naive1, 1),
                  		  			std::make_unique<RouletteSearch>(naive2, 1),
                  		  			1, 1, naive1, 0.0, 0.0, 10000.0,
                  		  			std::make_unique<timing::Uniform>(3.0, 30), 0))/*)*/.run();
	return 0;
}