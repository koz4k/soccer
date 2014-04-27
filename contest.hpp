#include "soccer/Contest.h"
#include "soccer/ai/MaxHeuristicSearch.h"
#include "soccer/ai/Negamax.h"
#include "soccer/ai/heur/naive.h"
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
		str << "negamax" << i;
		contest.addAi(str.str(), new ai::Negamax(ai::heur::naive1, i),
						 		 new ai::Negamax(ai::heur::naive2, i));
	}
	
	contest.addAi("random", new ai::MaxHeuristicSearch(ai::heur::uniform),
							new ai::MaxHeuristicSearch(ai::heur::uniform));
	contest.addAi("greedy", new ai::MaxHeuristicSearch(ai::heur::naive1),
							new ai::MaxHeuristicSearch(ai::heur::naive2));
	
	contest.run(100);
	std::cout << contest << std::endl;
	
	return 0;
}
