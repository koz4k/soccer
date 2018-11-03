#ifndef _soccer_SimpleMonteCarlo_h_
#define _soccer_SimpleMonteCarlo_h_

#include "../../GameState.h"
#include "../../Ai.h"
#include <memory>

namespace soccer { namespace ai { namespace heur {

class SimpleMonteCarlo
{
  public:
  	SimpleMonteCarlo(Ai* playoutAi1, Ai* playoutAi2, int playoutCount, Player me);
	/*SimpleMonteCarlo(const SimpleMonteCarlo&);
	SimpleMonteCarlo& operator=(const SimpleMonteCarlo&);*/
	SimpleMonteCarlo(SimpleMonteCarlo&& other);
	SimpleMonteCarlo& operator=(SimpleMonteCarlo&& other);
  	double operator()(const GameState& state, int ms);
  	
  private:
    std::unique_ptr<Ai> playoutAi1_;
    std::unique_ptr<Ai> playoutAi2_;
  	int playoutCount_;
  	Player me_;
  	double scale_;
};

} } }

#endif
