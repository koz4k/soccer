#include "soccer/contest/TwoTeam.h"
#include "soccer/contest/Full.h"
#include "soccer/ai/MonteCarloTreeSearch.h"
#include "soccer/ai/RouletteSearch.h"
#include "soccer/ai/MaxOfFewSearch.h"
#include "soccer/ai/AlphaBeta.h"
#include "soccer/ai/heur/ReboundAwareNaive.h"
#include "soccer/ai/heur/naive.h"
#include "soccer/timing/Uniform.h"
#include "soccer/ai/OldMcts.h"
#include <string>
#include <sstream>
#include <iostream>
#include <cmath>

using namespace soccer;
using namespace ai;
using namespace heur;

int main()
{
	contest::TwoTeam theContest(10000, 1, true);
	//contest::TwoTeam theContest(6000, 1, true);
	//contest::Full theContest(true, true);
	
	/*const double RS[] = {0, 10, 20, 30, 50, 100}; // najlepsze: 10
	const int R_COUNT = 6;*/
	/*const double LAMBDAS[] = {0.2, 0.4, 0.8, 1.6, 3.2, 6.4}; // najlepsze: 1.6
	const int LAMBDA_COUNT = 6;*/
	/*const double CS[] = {0.5, 0.6, 0.7, 0.8, 0.9, 1.0}; // najlepsze: 0.7 (do sprawdzenia!)
	const int C_COUNT = 6;*/
	/*const int KS[] = {1, 2, 3, 4, 5, 6, 8, 10, 12, 16};
	const int K_COUNT = 10;*/
	/*const double WS[] = {0.0, 0.001, 0.002, 0.003, 0.005, 0.01, 0.03, 0.1, 0.3, 1.0, 3.0, 10.0, 30.0, 100.0}; // najlepsze: 0.02 (do sprawdzenia!)
	const int W_COUNT = 14;*/
	/*const double BIAS_LAMBDAS[] = {0.002, 0.005, 0.3}; // najlepsze: 0.3
	const int BIAS_LAMBDA_COUNT = 3;*/
	/*const double BIAS_RS[] = {36, 44, 50}; // najlepsze: 36
	const int BIAS_R_COUNT = 3;*/
	/*const double T_MULS[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0}; // najlepsze: 6
	const int T_MUL_COUNT = 8;*/
	const double T_MULS[] = {4.8, 5.0, 5.2, 5.4, 5.6, 5.8, 6.0, 6.2};
	const int T_MUL_COUNT = 8;
	for(int i = 0; i < 1/*T_MUL_COUNT*/; ++i)
	{
		std::stringstream str;
		str << "mcts " << T_MULS[i];
		/*theContest.addAi(str.str(), new MonteCarloTreeSearch(new RouletteSearch(ReboundAwareNaive(10.0, PLAYER_1), 1.6),
			                              		  			 new RouletteSearch(ReboundAwareNaive(10.0, PLAYER_2), 1.6),
			                              		  			 1, 0.5, ReboundAwareNaive(36.0, PLAYER_1), 0.02, 0.3, 1e9,
			                              		  			 new timing::Uniform(4.0, 2)),
			                        new MonteCarloTreeSearch(new RouletteSearch(ReboundAwareNaive(10.0, PLAYER_1), 1.6),
			                             		  			 new RouletteSearch(ReboundAwareNaive(10.0, PLAYER_2), 1.6),
			                              		  			 1, 0.5, ReboundAwareNaive(36.0, PLAYER_2), 0.02, 0.3, 1e9,
			                              		  			 new timing::Uniform(4.0, 2)));*/
		theContest.addAi(str.str(), new OldMcts(new RouletteSearch(ReboundAwareNaive(10.0, PLAYER_1), 1.6),
			                              		  			 new RouletteSearch(ReboundAwareNaive(36.0, PLAYER_2), 1.6), 2000, 1, 0.5),
			                        new OldMcts(new RouletteSearch(ReboundAwareNaive(10.0, PLAYER_1), 1.6),
			                              		  			 new RouletteSearch(ReboundAwareNaive(36.0, PLAYER_2), 1.6), 2000, 1, 0.5));
	}
	
	theContest.addAi("alpha beta 5", new AlphaBeta(naive1, 5),
					 		    	 new AlphaBeta(naive2, 5));
	
	
	theContest.run(100);
	std::cout << theContest << std::endl;
	
	return 0;
}