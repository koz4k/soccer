#include "soccer/contest/TwoTeam.h"
#include "soccer/contest/Full.h"
#include "soccer/ai/MonteCarloTreeSearch.h"
#include "soccer/ai/OldMcts.h"
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

void addMcts(Contest& theContest)
{
	theContest.addAi("mcts 10000", new OldMcts(new RouletteSearch(naive1, 1.6),
			                              		  			  new RouletteSearch(naive2, 1.6),
			                              		  			  10000, 1, 0.5),
			                         new OldMcts(new RouletteSearch(naive1, 1.6),
			                              		  			  new RouletteSearch(naive2, 1.6),
			                              		  			  10000, 1, 0.5));
}

void addAb(Contest& theContest)
{
	theContest.addAi("alpha beta 10", new AlphaBeta(naive1, 10), new AlphaBeta(naive2, 10));
}

int main(int argc, char* argv[])
{
	contest::TwoTeam theContest(6000, 1, true);
	
	bool rev = argc >= 2 && atoi(argv[1]) == 1;
	if(!rev)
	{
		addMcts(theContest);
		addAb(theContest);
	}
	else
	{
		addAb(theContest);
		addMcts(theContest);
	}
	
	theContest.run(100);
	std::cout << theContest << std::endl;
	
	return 0;
}