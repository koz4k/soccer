#include "MonteCarloTreeSearch.h"
#include "mcts/Tree.h"

namespace soccer { namespace ai {

using namespace mcts;

MonteCarloTreeSearch::MonteCarloTreeSearch(Ai* playoutAi1, Ai* playoutAi2,
										   int playoutCount, int n0, double c):
	playoutAi1_(playoutAi1), playoutAi2_(playoutAi2), playoutCount_(playoutCount), n0_(n0), c_(c)
{
}

MonteCarloTreeSearch::~MonteCarloTreeSearch()
{
	delete playoutAi1_;
	delete playoutAi2_;
}

Direction MonteCarloTreeSearch::move(const GameState& state, int ms
#ifdef DEBUG
		, std::list<Direction>& moveSequence
#endif
	)
{
	int oldN0 = Tree::n0;
	Tree::n0 = n0_;
	double oldC = Tree::c;
	Tree::c = c_;

	GameState stateCopy = state;
	Tree* tree = new Tree(state.whoseTurn());
	for(int i = 0; i < playoutCount_; ++i)
		tree->playout(stateCopy, playoutAi1_, playoutAi2_);
	Direction direction = tree->chooseMove();
//tree->print();
	
#ifdef DEBUG
	moveSequence.clear();
	tree->chooseMoveSequence(moveSequence);
#endif

	delete tree;
	
	Tree::n0 = oldN0;
	Tree::c = oldC;
	
	return direction;
}
	
} }