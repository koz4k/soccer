#include "Contest.h"
#include "Judge.h"
#include <algorithm>
#include <ctime>

namespace soccer {

Contest::Contest():
	repetitions_(0)
{
}

Contest::~Contest()
{
	for(int i = 0; i < ais1_.size(); ++i)
		delete ais1_[i];
	
	for(int i = 0; i < ais2_.size(); ++i)
		delete ais2_[i];
}

void Contest::addAi(std::string name, Ai* ai1, Ai* ai2)
{
	ais1_.push_back(ai1);
	ais2_.push_back(ai2);
	names_.push_back(std::move(name));
}

void Contest::run(int repetitions)
{
	int n = ais1_.size();
	if(data_.size() != n * n)
	{
		data_.resize(n * n);
		std::fill(data_.begin(), data_.end(), std::make_pair(0, 0));
		repetitions_ = 0;
	}
	
	for(int i = 0; i < ais1_.size(); ++i)
	{
		for(int j = 0; j < ais2_.size(); ++j)
		{
			Judge judge(ais1_[i], ais2_[j]);
			int wins = 0;
			clock_t t = clock();
			for(int r = 0; r < repetitions; ++r)
				wins += judge.run().whoWon() == PLAYER_1;
			t = clock() - t;
			getData_(i, j).first += wins;
			getData_(i, j).second += t;
		}
	}
	
	repetitions_ += repetitions;
}

std::ostream& operator<<(std::ostream& out, const Contest& contest)
{
	out << "contest report after " << contest.repetitions_ << " repetitions:" << std::endl;
	for(int i = 0; i < contest.ais1_.size(); ++i)
	{
		for(int j = 0; j < contest.ais2_.size(); ++j)
		{
			std::pair<int, int> data1 = contest.getData_(i, j);
			std::pair<int, int> data2 = contest.getData_(j, i);
			out << contest.names_[i] << " vs " << contest.names_[j] << ": "
				<< ((double) data1.first) / contest.repetitions_ << " / "
				<< ((double) data2.first) / contest.repetitions_ << ", time in ms: "
				<< ((double) data1.second) / CLOCKS_PER_SEC * 1000 / contest.repetitions_ << " / "
				<< ((double) data2.second) / CLOCKS_PER_SEC * 1000 / contest.repetitions_
				<< std::endl;
		}
	}
	
	return out;
}

std::pair<int, int>& Contest::getData_(int i, int j)
{
	return data_[ais1_.size() * i + j];
}

std::pair<int, int> Contest::getData_(int i, int j) const
{
	return data_[ais1_.size() * i + j];
}

}