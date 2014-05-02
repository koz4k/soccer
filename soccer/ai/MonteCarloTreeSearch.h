#ifndef _Soccer_MonteCarloTreeSearch_h_
#define _Soccer_MonteCarloTreeSearch_h_

#include "../Ai.h"

namespace soccer { namespace ai {

class MonteCarloTreeSearch: public Ai
{
  public:
  	MonteCarloTreeSearch(Ai* playoutAi1, Ai* playoutAi2, int playoutCount, int n0, double c);
  	~MonteCarloTreeSearch();
  	virtual Direction move(const GameState& state, int ms
#ifdef DEBUG
		, std::list<Direction>& moveSequence
#endif
  		);

  private:
  	Ai* playoutAi1_;
  	Ai* playoutAi2_;
  	int playoutCount_;
  	int n0_;
  	double c_;
};
	
} }

#endif
