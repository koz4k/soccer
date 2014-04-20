#include "soccer/Contest.h"
#include "soccer/ai/Negamax.h"
#include "soccer/ai/Greedy.h"
#include "soccer/ai/DeepGreedy.h"
#include "soccer/ai/Random.h"
#include <string>
#include <sstream>
#include <iostream>
#include <cmath>

using namespace soccer;

double naiveHeuristic1(const GameState& state)
{
	Vector2 position = state.getCurrentPosition();
	
	if(state.isGameOver())
		return position.y == 6 ? INFINITY : -INFINITY;
	
	return std::max(6 + position.y, -std::abs(position.x)) -
		   std::max(6 - position.y, -std::abs(position.x));
}

double naiveHeuristic2(const GameState& state)
{
	Vector2 position = state.getCurrentPosition();
	
	if(state.isGameOver())
		return position.y == -6 ? INFINITY : -INFINITY;
	
	return std::max(6 - position.y, -std::abs(position.x)) -
		   std::max(6 + position.y, -std::abs(position.x));
}

int main()
{
	Contest contest;
	for(int i = 1; i <= 7; ++i)
	{
		std::stringstream str;
		str << "negamax" << i;
		contest.addAi(str.str(), new ai::Negamax(naiveHeuristic1, i),
						 		 new ai::Negamax(naiveHeuristic2, i));
	}
	
	contest.addAi("random", new ai::Random(), new ai::Random());
	contest.addAi("greedy", new ai::Greedy(naiveHeuristic1),
							new ai::Greedy(naiveHeuristic2));
	
	contest.run(100);
	std::cout << contest << std::endl;
	
	return 0;
}