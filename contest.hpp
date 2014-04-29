#include "soccer/Contest.h"
#include "soccer/ai/Negamax.h"
#include "soccer/ai/MaxHeuristicSearch.h"
#include "soccer/ai/RandomHeuristicSearch.h"
#include "soccer/ai/heur/naive.h"
#include "soccer/ai/heur/smartUniform.h"
#include "soccer/ai/heur/uniform.h"
#include <string>
#include <sstream>
#include <iostream>
#include <cmath>

using namespace soccer;

int main()
{
	Contest contest;
	
	for(int i = 1; i <= 4; ++i)
	{
		std::stringstream str;
		str << "negamax " << i;
		contest.addAi(str.str(), new ai::Negamax(ai::heur::naive1, i),
						 		 new ai::Negamax(ai::heur::naive2, i));
	}
	
	contest.addAi("uniform random", new ai::MaxHeuristicSearch(ai::heur::uniform),
							     	new ai::MaxHeuristicSearch(ai::heur::uniform));
	
	contest.addAi("smart random", new ai::MaxHeuristicSearch(ai::heur::smartUniform1),
								  new ai::MaxHeuristicSearch(ai::heur::smartUniform2));
	
	/*const double LAMBDAS[] = {0.1, 0.2, 0.3, 0.5, 0.8, 1.2, 1.6, 2.0, 2.5, 3.0};	
	const int LAMBDA_COUNT = 10;
	for(int i = 0; i < LAMBDA_COUNT; ++i)
	{
		std::stringstream str;
		str << "naive random " << LAMBDAS[i];
		contest.addAi(str.str(), new ai::RandomHeuristicSearch(ai::heur::naive1, LAMBDAS[i]),
		              			 new ai::RandomHeuristicSearch(ai::heur::naive2, LAMBDAS[i]));
	}*/
	
	contest.run(100);
	std::cout << contest << std::endl;
	
	return 0;
}
