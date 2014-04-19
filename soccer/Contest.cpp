#include "Contest.h"
#include "Judge.h"
#include <algorithm>

namespace soccer {

Contest::Contest():
	repetitions_(0)
{
}

Contest::~Contest()
{
	for(int i = 0; i < ais_.size(); ++i)
		delete ais_[i];
}

void Contest::addAi(const char* name, Ai* ai)
{
	ais_.push_back(ai);
	names_.push_back(name);
}

void Contest::run(int repetitions)
{
	int n = ais_.size();
	if(wins_.size() != n * n)
	{
		wins_.resize(n * n);
		std::fill(wins_.begin(), wins_.end(), 0);
		repetitions_ = 0;
	}
	
	for(int i = 0; i < ais_.size(); ++i)
	{
		for(int j = i + 1; j < ais_.size(); ++j)
		{
			Judge judge(*ais_[i], *ais_[j]);
			for(int r = 0; r < repetitions; ++r)
			{
				GameState state = judge.run();
				if(state.whoWon() == PLAYER_1)
					++getWins_(i, j);
				else if(state.whoWon() == PLAYER_2)
					++getWins_(j, i);
			}
		}
	}
	
	repetitions_ += repetitions;
}
  	
std::ostream& operator<<(std::ostream& out, const Contest& contest)
{
	out << "contest report after " << contest.repetitions_ << " repetitions:" << std::endl;
	for(int i = 0; i < contest.ais_.size(); ++i)
	{
		for(int j = i + 1; j < contest.ais_.size(); ++j)
		{
			out << contest.names_[i] << " vs " << contest.names_[j] << ": "
				<< contest.getWins_(i, j) << " / " << contest.getWins_(j, i) << std::endl;
		}
	}
	out << std::endl;
}

int& Contest::getWins_(int i, int j)
{
	return wins_[ais_.size() * i + j];
}


int Contest::getWins_(int i, int j) const
{
	return wins_[ais_.size() * i + j];
}

}