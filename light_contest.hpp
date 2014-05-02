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
	
	for(int i = 1; i <= 3; ++i)
	{
		std::stringstream str;
		str << "negamax " << i;
		contest.addAi(str.str(), new Negamax(naive1, i),
						 		 new Negamax(naive2, i));
	}
	const double LAMBDAS[] = {1.2, 1.6, 2.0};	
	const int LAMBDA_COUNT = 3;
	for(int i = 0; i < LAMBDA_COUNT; ++i)
	{
		std::stringstream str1, str2;
		/*str1 << "monte carlo " << LAMBDAS[i];
		contest.addAi(str1.str(), new MaxHeuristicSearch(SimpleMonteCarlo(new RandomHeuristicSearch(naive1, LAMBDAS[i]),
	                                                                      new RandomHeuristicSearch(naive2, LAMBDAS[i]),
	                                                                      20, PLAYER_1)),
	                              new MaxHeuristicSearch(SimpleMonteCarlo(new RandomHeuristicSearch(naive1, LAMBDAS[i]),
	                                                                      new RandomHeuristicSearch(naive2, LAMBDAS[i]),
	                                                                      20, PLAYER_2)));*/
		
		str2 << "negamax monte carlo " << LAMBDAS[i];
		contest.addAi(str2.str(), new Negamax(SimpleMonteCarlo(new RandomHeuristicSearch(naive1, LAMBDAS[i]),
		                                                       new RandomHeuristicSearch(naive2, LAMBDAS[i]),
		                                                       20, PLAYER_1), 2),
		                          new Negamax(SimpleMonteCarlo(new RandomHeuristicSearch(naive1, LAMBDAS[i]),
		                                                       new RandomHeuristicSearch(naive2, LAMBDAS[i]),
		                                                       20, PLAYER_2), 2));
	}
	
	contest.addAi("negamax monte carlo smart uniform", new Negamax(SimpleMonteCarlo(new RandomHeuristicSearch(smartUniform1, 1),
					                                                                new RandomHeuristicSearch(smartUniform2, 1),
                                                                      				20, PLAYER_1), 2),
                              					 	   new Negamax(SimpleMonteCarlo(new RandomHeuristicSearch(smartUniform1, 1),
                                                                      				new RandomHeuristicSearch(smartUniform2, 1),
	                                                                      			20, PLAYER_2), 2));
	
	contest.run(3);
	std::cout << contest << std::endl;
	
	return 0;
}