#include "MonteCarloTreeSearch.h"
#include "mcts/Tree.h"
#include <cstdlib>
#include <ctime>

#include <cstdio>

namespace soccer { namespace ai {

using namespace mcts;

MonteCarloTreeSearch::MonteCarloTreeSearch(std::unique_ptr<Ai> playoutAi1,
                                           std::unique_ptr<Ai> playoutAi2,
										   int n0, double c, Heuristic heuristic,
										   double w, double lambda, double b,
										   std::unique_ptr<TimingStrategy> timing,
                                           int playoutCount):
	playoutAi1_(std::move(playoutAi1)), playoutAi2_(std::move(playoutAi2)), n0_(n0), c_(c), heuristic_(heuristic),
	w_(w), lambda_(lambda), b_(b), timing_(std::move(timing)), playoutCount_(playoutCount)
{
	srand(time(nullptr));
}

Direction MonteCarloTreeSearch::move(GameState& state, int ms
#ifdef DEBUG
		, std::list<Direction>& moveSequence
#endif
	)
{
	timing_->setGameState(state);
	timing_->start(ms);
	
	Tree::n0 = n0_;
	Tree::c = c_;
	Tree::heuristic = heuristic_;
	Tree::w = w_;
	Tree::lambda = lambda_;
	Tree::b = b_;

	if(!tree_)
		tree_ = std::make_unique<Tree>(state.whoseTurn());

	GameState stateCopy = state;
	int i = 0;
	//for(; timing_->haveTime() && !tree_->isSolved(); ++i)
	for(int i = 0; (playoutCount_ > 0 ? i < playoutCount_ : timing_->haveTime()) && !tree_->isSolved(); ++i)
		tree_->playout(stateCopy, playoutAi1_.get(), playoutAi2_.get());
	Direction direction = tree_->chooseMove();
	
	//printf("playouts: %d, direction: %d\n", i, direction);
	//fflush(stdout);
	
	// duct tape fix (to sie nie powinno zdarzyc, ale na wszelki wypadek)
	if(direction == DIR_END)
		for(direction = DIR_BEGIN; direction < DIR_END && !state.canMove(direction); ++direction);
	// duct tape fix #2 (gdy wszystkie srodki zawioda, robimy cokolwiek)
	if(direction == DIR_END)
		direction = rand() % DIR_END;
	
//tree->print();

#ifdef DEBUG
	moveSequence.clear();
	tree_->chooseMoveSequence(moveSequence);
#endif

	tree_ = tree_->move(direction);
	
	//printf("time left: %d\n", timing_->getTimeAvailable());
	//fflush(stdout);
	//if(tree_->isSolved())
	//	printf("solved: %d\n", tree_->isWinning()), fflush(stdout);
	timing_->stop();
	
	return direction;
}

void MonteCarloTreeSearch::opponentMoved(Direction direction)
{
	if(tree_)
		tree_ = tree_->move(direction);
}

void MonteCarloTreeSearch::reset()
{
    tree_.reset();
}
	
} }
