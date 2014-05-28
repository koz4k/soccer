#ifndef _Soccer_MonteCarloTreeSearch_h_
#define _Soccer_MonteCarloTreeSearch_h_

#include "../Ai.h"
#include "mcts/Tree.h"
#include "../TimingStrategy.h"

namespace soccer { namespace ai {

class MonteCarloTreeSearch: public Ai
{
  public:
  	MonteCarloTreeSearch(Ai* playoutAi1, Ai* playoutAi2,
  						 int n0, double c,
  						 Heuristic heuristic, double w, double lambda, double b,
  						 TimingStrategy* timing, int playoutCount);
  	~MonteCarloTreeSearch();
  	virtual Direction move(GameState& state, int ms
#ifdef DEBUG
		, std::list<Direction>& moveSequence
#endif
  		);
	virtual void opponentMoved(Direction direction);
	virtual void reset();

  private:
  	Ai* playoutAi1_;
  	Ai* playoutAi2_;
  	int n0_;
  	double c_;
  	Heuristic heuristic_;
  	double w_;
  	double lambda_;
  	double b_;
  	mcts::Tree* tree_;
  	TimingStrategy* timing_;
  int playoutCount_;
};
	
} }

#endif