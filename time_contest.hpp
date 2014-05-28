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

int main(int argc, char* argv[])
{
	int depth = 1;
	if(argc > 1)
		depth = atoi(argv[1]);
	
	contest::Full theContest(4000, true, true);
	
	theContest.addAi("mcts", new MonteCarloTreeSearch(new RouletteSearch(naive1, 1),
                  		  			new RouletteSearch(naive2, 1),
                  		  			1, 1, naive1, 0.01, 0.1, 1e5,
                  		  			new timing::Uniform(4.0, 2), 0),
					 		    new MonteCarloTreeSearch(new RouletteSearch(naive1, 1),
                  		  			new RouletteSearch(naive2, 1),
                  		  			1, 1, naive2, 0.01, 0.1, 1e5,
                  		  			new timing::Uniform(4.0, 2), 0));
	theContest.run(8);
	std::cout << theContest << std::endl;
	
	/*contest::Full theContest = contest::Full(0, true, true);
	theContest.addAi("mcts 2800", new MonteCarloTreeSearch(new RouletteSearch(naive1, 3),
                  		  			new RouletteSearch(naive2, 3),
                  		  			1, 1, naive1, 0, 0, 1e9,
                  		  			new timing::Uniform(4.0, 2), 2500),
	                             new MonteCarloTreeSearch(new RouletteSearch(naive1, 3),
                  		  			new RouletteSearch(naive2, 3),
                  		  			1, 1, naive2, 0, 0, 1e9,
                  		  			new timing::Uniform(4.0, 2), 2500));
	theContest.run(8);
	std::cout << theContest << std::endl;*/
	
	return 0;
}