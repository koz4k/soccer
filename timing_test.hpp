#include "soccer/Judge.h"
#include "soccer/ai/MonteCarloTreeSearch.h"
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

int main()
{
	Judge judge(new AlphaBeta(naive1, 10),
	            new MonteCarloTreeSearch(new RouletteSearch(ReboundAwareNaive(10.0, PLAYER_1), 1.6),
                 		  				 new RouletteSearch(ReboundAwareNaive(10.0, PLAYER_2), 1.6),
                  		  				 1, 0.5, ReboundAwareNaive(36.0, PLAYER_2), 0.02, 0.3,
                  		  				 new timing::Uniform(5.0, 3)),
                60000);
	GameState state = judge.run();
	std::cout << (state.whoWon() == PLAYER_1 ? "alpha beta" : "mcts") << " won" << std::endl;
	
	return 0;
}