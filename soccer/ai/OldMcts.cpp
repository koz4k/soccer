#include "OldMcts.h"
#include "mcts/OldTree.h"

namespace soccer { namespace ai {

using namespace mcts;

OldMcts::OldMcts(Ai* playoutAi1, Ai* playoutAi2,
										   int playoutCount, int n0, double c):
	playoutAi1_(playoutAi1), playoutAi2_(playoutAi2), playoutCount_(playoutCount), n0_(n0), c_(c)
{
}

OldMcts::~OldMcts()
{
	delete playoutAi1_;
	delete playoutAi2_;
}

Direction OldMcts::move(GameState& state, int ms
#ifdef DEBUG
		, std::list<Direction>& moveSequence
#endif
	)
{
	OldTree::n0 = n0_;
	OldTree::c = c_;

	GameState stateCopy = state;
	OldTree* tree = new OldTree(state.whoseTurn());
	for(int i = 0; i < playoutCount_; ++i)
		tree->playout(stateCopy, playoutAi1_, playoutAi2_);
	Direction direction = tree->chooseMove();
//tree->print();
	
#ifdef DEBUG
	moveSequence.clear();
	tree->chooseMoveSequence(moveSequence);
#endif

	delete tree;
	
	return direction;
}
	
} }