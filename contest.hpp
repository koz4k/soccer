#include "soccer/Contest.h"
#include "soccer/ai/ShallowHeuristicSearch.h"
#include "soccer/ai/Negamax.h"
#include "soccer/ai/heur/Negamax.h"
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
	
	for(int i = 1; i <= 5; ++i)
	{
		std::stringstream str;
		str << "old negamax" << i;
		contest.addAi(str.str(), new ai::Negamax(ai::heur::naive1, i),
						 		 new ai::Negamax(ai::heur::naive2, i));
	}
	
	for(int i = 0; i < 5; ++i)
	{
		std::stringstream str;
		str << "new negamax" << i + 1;
		contest.addAi(str.str(), new ai::ShallowHeuristicSearch(ai::heur::Negamax(ai::heur::naive1, i)),
						 		 new ai::ShallowHeuristicSearch(ai::heur::Negamax(ai::heur::naive2, i)));
	}
	
	contest.addAi("random", new ai::ShallowHeuristicSearch(ai::heur::uniform),
							new ai::ShallowHeuristicSearch(ai::heur::uniform));
	contest.addAi("greedy", new ai::ShallowHeuristicSearch(ai::heur::naive1),
							new ai::ShallowHeuristicSearch(ai::heur::naive2));
	
	contest.run(100);
	std::cout << contest << std::endl;
	
	return 0;
}