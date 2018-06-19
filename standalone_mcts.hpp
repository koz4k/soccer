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
	/*AiStandalone(new MonteCarloTreeSearch(new RouletteSearch(ReboundAwareNaive(10.0, PLAYER_1), 1.6),
	                              		  new RouletteSearch(ReboundAwareNaive(10.0, PLAYER_2), 1.6),
	                              		  1, 0.5, ReboundAwareNaive(36.0, PLAYER_1), 0.02, 0.3, 1e9,
	                              		  new timing::Uniform(3.0, 3))).run();*/
	                              		  
	AiStandalone(/*new WithOpenings("pk346962-openings1.dat", "pk346962-openings2.dat",*/ new MonteCarloTreeSearch(new RouletteSearch(naive1, 1),
                  		  			new RouletteSearch(naive2, 1),
                  		  			1, 1, naive1, 0.0, 0.0, 10000.0,
                  		  			new timing::Uniform(3.0, 30), 0))/*)*/.run();
	return 0;
}