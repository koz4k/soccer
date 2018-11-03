#include "soccer/contest/TwoTeam.h"
#include "soccer/contest/Full.h"
#include "soccer/ai/MonteCarloTreeSearch.h"
#include "soccer/ai/RouletteSearch.h"
#include "soccer/ai/MaxOfFewSearch.h"
#include "soccer/ai/AlphaBeta.h"
#include "soccer/ai/heur/ReboundAwareNaive.h"
#include "soccer/ai/heur/naive.h"
#include "soccer/timing/Uniform.h"
#include <string>
#include <sstream>
#include <iostream>
#include <cmath>

using namespace soccer;
using namespace ai;
using namespace heur;

int main()
{
	{
		contest::TwoTeam theContest(6000, 1, true);
		
		theContest.addAi("mcts 10000", std::make_unique<MonteCarloTreeSearch>(std::make_unique<RouletteSearch>(naive1, 1.6),
		                              		  			  std::make_unique<RouletteSearch>(naive2, 1.6),
		                              		  			  1, 0.5, naive1, 0, 1, 1e9,
		                              		  			  std::make_unique<timing::Uniform>(5.0, 2), 10000),
		                         std::make_unique<MonteCarloTreeSearch>(std::make_unique<RouletteSearch>(naive1, 1.6),
		                              		  			  std::make_unique<RouletteSearch>(naive2, 1.6),
		                              		  			  1, 0.5, naive2, 0, 1, 1e9,
		                              		  			  std::make_unique<timing::Uniform>(5.0, 2), 10000));
		
		theContest.addAi("alpha beta 5", std::make_unique<AlphaBeta>(naive1, 5), std::make_unique<AlphaBeta>(naive2, 5));
		theContest.addAi("alpha beta 8", std::make_unique<AlphaBeta>(naive1, 8), std::make_unique<AlphaBeta>(naive2, 8));
		theContest.addAi("alpha beta 10", std::make_unique<AlphaBeta>(naive1, 10), std::make_unique<AlphaBeta>(naive2, 10));
		
		theContest.run(100);
		std::cout << theContest << std::endl;
	}
	
	{
		contest::TwoTeam theContest(6000, 1, true);
		
		theContest.addAi("mcts 10000", std::make_unique<MonteCarloTreeSearch>(std::make_unique<RouletteSearch>(naive1, 1.6),
		                              		  			  std::make_unique<RouletteSearch>(naive2, 1.6),
		                              		  			  1, 0.5, naive1, 0, 1, 1e9,
		                              		  			  std::make_unique<timing::Uniform>(5.0, 2), 10000),
		                         std::make_unique<MonteCarloTreeSearch>(std::make_unique<RouletteSearch>(naive1, 1.6),
		                              		  			  std::make_unique<RouletteSearch>(naive2, 1.6),
		                              		  			  1, 0.5, naive2, 0, 1, 1e9,
		                              		  			  std::make_unique<timing::Uniform>(5.0, 2), 10000));
		
		theContest.addAi("alpha beta 13", std::make_unique<AlphaBeta>(naive1, 13), std::make_unique<AlphaBeta>(naive2, 13));
		
		theContest.run(50);
		std::cout << theContest << std::endl;
	}
	
	{
		contest::TwoTeam theContest(6000, 1, true);
		
		theContest.addAi("mcts 20000", std::make_unique<MonteCarloTreeSearch>(std::make_unique<RouletteSearch>(naive1, 1.6),
		                              		  			  std::make_unique<RouletteSearch>(naive2, 1.6),
		                              		  			  1, 0.5, naive1, 0, 1, 1e9,
		                              		  			  std::make_unique<timing::Uniform>(5.0, 2), 20000),
		                         std::make_unique<MonteCarloTreeSearch>(std::make_unique<RouletteSearch>(naive1, 1.6),
		                              		  			  std::make_unique<RouletteSearch>(naive2, 1.6),
		                              		  			  1, 0.5, naive2, 0, 1, 1e9,
		                              		  			  std::make_unique<timing::Uniform>(5.0, 2), 20000));
		
		theContest.addAi("alpha beta 13", std::make_unique<AlphaBeta>(naive1, 13), std::make_unique<AlphaBeta>(naive2, 13));
		
		theContest.run(30);
		std::cout << theContest << std::endl;
	}
	
	return 0;
}
