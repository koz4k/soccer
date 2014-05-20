#ifndef _Soccer_OldMcts_h_
#define _Soccer_OldMcts_h_

#include "../Ai.h"

namespace soccer { namespace ai {

class OldMcts: public Ai
{
  public:
  	OldMcts(Ai* playoutAi1, Ai* playoutAi2, int playoutCount, int n0, double c);
  	~OldMcts();
  	virtual Direction move(GameState& state, int ms
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