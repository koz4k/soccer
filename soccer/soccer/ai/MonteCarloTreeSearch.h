#ifndef _soccer_MonteCarloTreeSearch_h_
#define _soccer_MonteCarloTreeSearch_h_

#include "../Ai.h"
#include "mcts/Tree.h"
#include "../TimingStrategy.h"
#include <memory>

namespace soccer { namespace ai {

class MonteCarloTreeSearch: public Ai
{
  public:
  	MonteCarloTreeSearch(std::unique_ptr<Ai> playoutAi1, std::unique_ptr<Ai> playoutAi2,
  						 int n0, double c,
  						 Heuristic heuristic, double w, double lambda, double b,
  						 std::unique_ptr<TimingStrategy> timing, int playoutCount);
  	virtual Direction move(GameState& state, int ms
#ifdef DEBUG
		, std::list<Direction>& moveSequence
#endif
  		);
	virtual void opponentMoved(Direction direction);
	virtual void reset();

  private:
    std::unique_ptr<Ai> playoutAi1_;
    std::unique_ptr<Ai> playoutAi2_;
  	int n0_;
  	double c_;
  	Heuristic heuristic_;
  	double w_;
  	double lambda_;
  	double b_;
    std::unique_ptr<mcts::Tree> tree_;
    std::unique_ptr<TimingStrategy> timing_;
    int playoutCount_;
};
	
} }

#endif
