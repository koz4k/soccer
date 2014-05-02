#include "soccer/Contest.h"
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
	Contest contest;
	
	for(int i = 1; i <= 4; ++i)
	{
		std::stringstream str;
		str << "negamax " << i;
		contest.addAi(str.str(), new Negamax(naive1, i),
						 		 new Negamax(naive2, i));
	}
	
	contest.addAi("uniform random", new MaxHeuristicSearch(uniform),
							     	new MaxHeuristicSearch(uniform));
	
	contest.addAi("smart random", new MaxHeuristicSearch(smartUniform1),
								  new MaxHeuristicSearch(smartUniform2));
	
	//const double LAMBDAS[] = {0.1, 0.2, 0.3, 0.5, 0.8, 1.2, 1.6, 2.0, 2.5, 3.0};	
	//const int LAMBDA_COUNT = 10;
	const double LAMBDAS[] = {0.1, 0.3, 0.6, 0.8, 1.2, 1.4, 1.6, 1.8, 2.0, 3.0, 4.0};	
	const int LAMBDA_COUNT = 10;
	for(int i = 0; i < LAMBDA_COUNT; ++i)
	{
		std::stringstream str;
		str << "monte carlo " << LAMBDAS[i];
		contest.addAi(str.str(), new MaxHeuristicSearch(SimpleMonteCarlo(new RandomHeuristicSearch(naive1, LAMBDAS[i]),
	                                                                     new RandomHeuristicSearch(naive2, LAMBDAS[i]),
	                                                                     100, PLAYER_1)),
	                             new MaxHeuristicSearch(SimpleMonteCarlo(new RandomHeuristicSearch(naive1, LAMBDAS[i]),
	                                                                     new RandomHeuristicSearch(naive2, LAMBDAS[i]),
	                                                                     100, PLAYER_2)));
	}
	
	contest.addAi("monte carlo greedy", new MaxHeuristicSearch(SimpleMonteCarlo(new MaxHeuristicSearch(naive1),
                                                                     			new MaxHeuristicSearch(naive2),
			                                                                    100, PLAYER_1)),
                             			new MaxHeuristicSearch(SimpleMonteCarlo(new MaxHeuristicSearch(naive1),
                                        		                                new MaxHeuristicSearch(naive2),
                                                   			                    100, PLAYER_2)));
	
	contest.run(100);
	std::cout << contest << std::endl;
	
	return 0;
}
