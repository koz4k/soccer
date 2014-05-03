#include "soccer/FullContest.h"
#include "soccer/TwoTeamContest.h"
#include "soccer/ai/MonteCarloTreeSearch.h"
#include "soccer/ai/Negamax.h"
#include "soccer/ai/MaxHeuristicSearch.h"
#include "soccer/ai/RandomHeuristicSearch.h"
#include "soccer/ai/heur/SimpleMonteCarlo.h"
#include "soccer/ai/heur/naive.h"
#include "soccer/ai/heur/smartUniform.h"
#include "soccer/ai/heur/uniform.h"
#include <string>
#include <sstream>
#include <iostream>
#include <cmath>

using namespace soccer;
using namespace ai;
using namespace heur;

int main()
{
	TwoTeamContest contest(1, true);
	
	for(int d = 8; d <= 8; ++d)
	{
		std::stringstream str;
		str << "negamax " << d;
		contest.addAi(str.str(), new Negamax(naive1, d),
						 		 new Negamax(naive2, d));
	}
	
	for(int n0 = 1; n0 <= 7; ++n0)
	{
		std::stringstream str;
		str << "mcts " << n0;
		contest.addAi(str.str(), new MonteCarloTreeSearch(new RandomHeuristicSearch(naive1, 1.6),
	                              		  				  new RandomHeuristicSearch(naive2, 1.6),
	                              		  				  10000, n0, 1.4),
	                             new MonteCarloTreeSearch(new RandomHeuristicSearch(naive1, 1.6),
	                              		  				  new RandomHeuristicSearch(naive2, 1.6),
	                              		  				  10000, n0, 1.4));
	}
	
	contest.run(10);
	std::cout << contest << std::endl;
	
	return 0;
}