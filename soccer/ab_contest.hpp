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

std::unique_ptr<Ai> buildNaiveMcts(int playouts)
{
	return std::make_unique<MonteCarloTreeSearch>(std::make_unique<RouletteSearch>(naive1, 1),
                  		  			std::make_unique<RouletteSearch>(naive2, 1),
                  		  			1, 1, naive1, 0, 0, 1e9,
                  		  			std::make_unique<timing::Uniform>(4.0, 2), playouts);
}

std::unique_ptr<Ai> buildSafeMcts(int playouts)
{
	return std::make_unique<MonteCarloTreeSearch>(std::make_unique<RouletteSearch>(naive1, 1),
                  		  			std::make_unique<RouletteSearch>(naive2, 1),
                  		  			1, 1, safe1, 0, 0, 1e9,
                  		  			std::make_unique<timing::Uniform>(4.0, 2), playouts);
}

std::unique_ptr<Ai> buildRiskyMcts(int playouts)
{
	return std::make_unique<MonteCarloTreeSearch>(std::make_unique<RouletteSearch>(risky1, 1),
                  		  			std::make_unique<RouletteSearch>(risky2, 1),
                  		  			1, 1, risky1, 0, 0, 1e9,
                  		  			std::make_unique<timing::Uniform>(4.0, 2), playouts);
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
		
		theContest.addAi("naive", std::make_unique<AlphaBeta>(naive1, 13),
						 		  std::make_unique<AlphaBeta>(naive2, 13));
		theContest.addAi("safe", std::make_unique<AlphaBeta>(safe1, 13),
						 		 std::make_unique<AlphaBeta>(safe2, 13));
		theContest.addAi("risky", std::make_unique<AlphaBeta>(risky1, 13),
						 		  std::make_unique<AlphaBeta>(risky2, 13));
		
		theContest.run(32);
		std::cout << theContest << std::endl;
	}
	
	return 0;
}
