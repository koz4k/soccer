#include "soccer/contest/Full.h"
#include "soccer/contest/TwoTeam.h"
#include "soccer/contest/TwoTeam.h"
#include "soccer/ai/MonteCarloTreeSearch.h"
#include "soccer/ai/RouletteSearch.h"
#include "soccer/ai/AlphaBeta.h"
#include "soccer/ai/Negamax.h"
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

Ai* buildNaiveMcts(int playouts)
{
	return new MonteCarloTreeSearch(new RouletteSearch(naive1, 1),
                  		  			new RouletteSearch(naive2, 1),
                  		  			1, 1, naive1, 0, 0, 1e9,
                  		  			new timing::Uniform(4.0, 2), playouts);
}

Ai* buildSafeMcts(int playouts)
{
	return new MonteCarloTreeSearch(new RouletteSearch(naive1, 1),
                  		  			new RouletteSearch(naive2, 1),
                  		  			1, 1, safe1, 0, 0, 1e9,
                  		  			new timing::Uniform(4.0, 2), playouts);
}

Ai* buildRiskyMcts(int playouts)
{
	return new MonteCarloTreeSearch(new RouletteSearch(risky1, 1),
                  		  			new RouletteSearch(risky2, 1),
                  		  			1, 1, risky1, 0, 0, 1e9,
                  		  			new timing::Uniform(4.0, 2), playouts);
}

int main()
{
	{
		contest::Full theContest(1000000, false, true);
						 		
		theContest.addAi("naive", buildNaiveMcts(5000), buildNaiveMcts(5000));
		theContest.addAi("safe", buildNaiveMcts(5000), buildNaiveMcts(5000));
		theContest.addAi("risky", buildRiskyMcts(5000), buildRiskyMcts(5000));
		
		theContest.run(32);
		std::cout << theContest << std::endl;
	}

	{
		contest::Full theContest(1000000, false, true);
		
		theContest.addAi("naive", new AlphaBeta(naive1, 13),
						 		  new AlphaBeta(naive2, 13));
		theContest.addAi("safe", new AlphaBeta(safe1, 13),
						 		 new AlphaBeta(safe2, 13));
		theContest.addAi("risky", new AlphaBeta(risky1, 13),
						 		  new AlphaBeta(risky2, 13));
		
		theContest.run(32);
		std::cout << theContest << std::endl;
	}
	
	return 0;
}