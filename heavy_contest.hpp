#include "soccer/contest/Full.h"
#include "soccer/ai/Negamax.h"
#include "soccer/ai/MaxSearch.h"
#include "soccer/ai/RouletteSearch.h"
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
	contest::Full theContest;
	
	for(int i = 1; i <= 4; ++i)
	{
		std::stringstream str;
		str << "negamax " << i;
		theContest.addAi(str.str(), new Negamax(naive1, i),
				    		 		new Negamax(naive2, i));
	}
	
	theContest.addAi("uniform random", new MaxSearch(uniform),
			    				       new MaxSearch(uniform));
	
	theContest.addAi("smart random", new MaxHeuristicSearch(smartUniform1),
								     new MaxHeuristicSearch(smartUniform2));
	
	//const double LAMBDAS[] = {0.1, 0.2, 0.3, 0.5, 0.8, 1.2, 1.6, 2.0, 2.5, 3.0};	
	//const int LAMBDA_COUNT = 10;
	const double LAMBDAS[] = {0.1, 0.3, 0.6, 0.8, 1.2, 1.4, 1.6, 1.8, 2.0, 3.0, 4.0};	
	const int LAMBDA_COUNT = 10;
	for(int i = 0; i < LAMBDA_COUNT; ++i)
	{
		std::stringstream str;
		str << "monte carlo " << LAMBDAS[i];
		theContest.addAi(str.str(), new MaxHeuristicSearch(SimpleMonteCarlo(new RouletteSearch(naive1, LAMBDAS[i]),
	                                                                     	new RouletteSearch(naive2, LAMBDAS[i]),
	                                                                     	100, PLAYER_1)),
	                           	    new MaxHeuristicSearch(SimpleMonteCarlo(new RouletteSearch(naive1, LAMBDAS[i]),
	                                                                        new RouletteSearch(naive2, LAMBDAS[i]),
	                                                                        100, PLAYER_2)));
	}
	
	theContest.addAi("monte carlo greedy", new MaxHeuristicSearch(SimpleMonteCarlo(new MaxSearch(naive1),
                                                                        		   new MaxSearch(naive2),
			                                                                       100, PLAYER_1)),
                             			   new MaxHeuristicSearch(SimpleMonteCarlo(new MaxSearch(naive1),
                                           		                                   new MaxSearch(naive2),
                                                   			                       100, PLAYER_2)));
	
	theContest.run(100);
	std::cout << theContest << std::endl;
	
	return 0;
}
