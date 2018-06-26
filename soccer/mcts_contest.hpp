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

// najlepszy zestaw: c=1, lambda=1 (do 11/1200)

using namespace soccer;
using namespace ai;
using namespace heur;

Ai* buildMcts1(double param, int playouts)
{
	return new MonteCarloTreeSearch(new RouletteSearch(naive1, 1),
                  		  			new RouletteSearch(naive2, 1),
                  		  			1, 1, naive1, 0.01, 0.1, 1e5,
                  		  			new timing::Uniform(param, 2), playouts);
}

Ai* buildMcts2(double param, int playouts)
{
	return new MonteCarloTreeSearch(new RouletteSearch(naive1, 1),
                  		  			new RouletteSearch(naive2, 1),
                  		  			1, 1, naive2, 0.01, 0.1, 1e5,
                  		  			new timing::Uniform(param, 2), playouts);
}

void runContest(int t, int depth, int playouts, int repetitions)
{
	contest::TwoTeam theContest(t, 1, true);
	/*std::stringstream str;
	str << "alpha beta " << depth;
	theContest.addAi(str.str(), new AlphaBeta(naive1, depth),
					 		   	new AlphaBeta(naive2, depth));*/
	
	const double PARAMS[] = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0};
	const int PARAM_COUNT = 6;
	
	for(int i = 0; i < PARAM_COUNT; ++i)
	{
		std::stringstream str;
		str << "mcts " << PARAMS[i];
		int pl = i ? 0 : playouts;
		theContest.addAi(str.str(), buildMcts1(PARAMS[i], pl/*ayouts*/), buildMcts2(PARAMS[i], pl/*ayouts*/));
	}
	
	theContest.run(repetitions);
	std::cout << theContest << std::endl;
}

int main()
{
	runContest(2400, 10, 600, 64);
	runContest(9600, 12, 2400, 16);
	
	return 0;
}