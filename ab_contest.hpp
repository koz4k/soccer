#include "soccer/contest/Full.h"
#include "soccer/contest/TwoTeam.h"
#include "soccer/contest/Pairwise.h"
#include "soccer/ai/AlphaBeta.h"
#include "soccer/ai/Negamax.h"
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
	contest::Pairwise theContest(true);
	
	for(int d = 1; d <= 4; ++d)
	{
		std::stringstream str1, str2;
		str1 << "negamax " << d;
		theContest.addAi(str1.str(), new Negamax(naive1, d),
				   		 		     new Negamax(naive2, d));
		str2 << "alphabeta " << d;
		theContest.addAi(str2.str(), new AlphaBeta(naive1, d),
						 		     new AlphaBeta(naive2, d));
	}
	
	theContest.run(100);
	std::cout << theContest << std::endl;
	
	return 0;
}