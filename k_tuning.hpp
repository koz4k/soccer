#include "soccer/contest/TwoTeam.h"
#include "soccer/contest/Full.h"
#include "soccer/ai/MonteCarloTreeSearch.h"
#include "soccer/ai/RouletteSearch.h"
#include "soccer/ai/MaxOfFewSearch.h"
#include "soccer/ai/DeepMaxOfFewSearch.h"
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
	contest::TwoTeam theContest(2500, 1, true);
	//contest::Full theContest(true, true);
	
	theContest.addAi("alpha beta 10", new AlphaBeta(naive1, 10),
					 		    	  new AlphaBeta(naive2, 10));
	
	/*const double RS[] = {0, 10, 20, 30, 50, 100}; // najlepsze: 10
	const int R_COUNT = 6;*/
	/*const double LAMBDAS[] = {0.2, 0.4, 0.8, 1.6, 3.2, 6.4}; // najlepsze: 1.6
	const int LAMBDA_COUNT = 6;*/
	/*const double CS[] = {0.7, 0.8, 1.0, 1.2, 1.5, 1.8}; // najlepsze: 0.8
	const int C_COUNT = 6;*/
	const int KS[] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512};
	const int K_COUNT = 10;
	for(int i = 0; i < K_COUNT; ++i)
	{
		std::stringstream str;
		str << "mcts " << KS[i];
		theContest.addAi(str.str(), new MonteCarloTreeSearch(new DeepMaxOfFewSearch(naive1, KS[i]),
	                              		  				     new DeepMaxOfFewSearch(naive2, KS[i]),
	                              		  				     1, 0.5, ReboundAwareNaive(36.0, PLAYER_1), 0.02, 0.3,
	                              		  				     new timing::Uniform(4.0, 2)),
	                                new MonteCarloTreeSearch(new DeepMaxOfFewSearch(naive1, KS[i]),
	                              		  				     new DeepMaxOfFewSearch(naive2, KS[i]),
	                              		  				     1, 0.5, ReboundAwareNaive(36.0, PLAYER_2), 0.02, 0.3,
	                              		  				     new timing::Uniform(4.0, 2)));
	}
	
	theContest.run(100);
	std::cout << theContest << std::endl;
	
	return 0;
}