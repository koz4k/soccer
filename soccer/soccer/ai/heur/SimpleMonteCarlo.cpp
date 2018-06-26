#include "SimpleMonteCarlo.h"
#include "../../Judge.h"

namespace soccer { namespace ai { namespace heur {

SimpleMonteCarlo::SimpleMonteCarlo(Ai* playoutAi1, Ai* playoutAi2,
								   int playoutCount, Player me):
	playoutAi1_(playoutAi1), playoutAi2_(playoutAi2),
	playoutCount_(playoutCount), me_(me)
{
}

// brzydki hack spowodowany tym, ze funktor trzymany w std::function musi byc CopyConstructible
SimpleMonteCarlo::SimpleMonteCarlo(const SimpleMonteCarlo& other):
	playoutAi1_(other.playoutAi1_), playoutAi2_(other.playoutAi2_),
	playoutCount_(other.playoutCount_), me_(other.me_)
{
	const_cast<SimpleMonteCarlo&>(other).playoutAi1_ =
		const_cast<SimpleMonteCarlo&>(other).playoutAi2_ = nullptr;
}

SimpleMonteCarlo& SimpleMonteCarlo::operator=(const SimpleMonteCarlo& other)
{
	playoutAi1_ = other.playoutAi1_;
	playoutAi2_ = other.playoutAi2_;
	playoutCount_ = other.playoutCount_;
	me_ = other.me_;
	
	const_cast<SimpleMonteCarlo&>(other).playoutAi1_ =
		const_cast<SimpleMonteCarlo&>(other).playoutAi2_ = nullptr;
}

SimpleMonteCarlo::SimpleMonteCarlo(SimpleMonteCarlo&& other):
	playoutAi1_(other.playoutAi1_), playoutAi2_(other.playoutAi2_),
	playoutCount_(other.playoutCount_), me_(other.me_)
{
	other.playoutAi1_ = other.playoutAi2_ = nullptr;
}

SimpleMonteCarlo& SimpleMonteCarlo::operator=(SimpleMonteCarlo&& other)
{
	playoutAi1_ = other.playoutAi1_;
	playoutAi2_ = other.playoutAi2_;
	playoutCount_ = other.playoutCount_;
	me_ = other.me_;
	
	other.playoutAi1_ = other.playoutAi2_ = nullptr;
}

SimpleMonteCarlo::~SimpleMonteCarlo()
{
	delete playoutAi1_;
	delete playoutAi2_;
}

double SimpleMonteCarlo::operator()(const GameState& state, int ms)
{	
	int wins = 0;
	for(int i = 0; i < playoutCount_; ++i)
		wins += Judge(playoutAi1_, playoutAi2_, state).run().whoWon() == me_;
	return ((double) wins) / playoutCount_;
}

} } }