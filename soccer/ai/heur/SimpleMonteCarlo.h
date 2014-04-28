#ifndef _Soccer_SimpleMonteCarlo_h_
#define _Soccer_SimpleMonteCarlo_h_

#include "../../GameState.h"
#include "../../Ai.h"

namespace soccer { namespace ai { namespace heur {

class SimpleMonteCarlo
{
  public:
  	SimpleMonteCarlo(Ai* playoutAi1, Ai* playoutAi2, int playoutCount, Player me);
	SimpleMonteCarlo(const SimpleMonteCarlo&);
	SimpleMonteCarlo& operator=(const SimpleMonteCarlo&);
	SimpleMonteCarlo(SimpleMonteCarlo&& other);
	SimpleMonteCarlo& operator=(SimpleMonteCarlo&& other);
	~SimpleMonteCarlo();
  	double operator()(const GameState& state, int ms);
  	
  private:
  	Ai* playoutAi1_;
  	Ai* playoutAi2_;
  	int playoutCount_;
  	Player me_;
  	double scale_;
};

} } }

#endif