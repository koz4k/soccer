#ifndef _Soccer_WithOpenings_h_
#define _Soccer_WithOpenings_h_

#include "../Ai.h"
#include "open/Move.h"

namespace soccer { namespace ai {

class WithOpenings: public Ai
{
  public:
  	WithOpenings(const std::string& file1, const std::string& file2, Ai* mainAi);
  	~WithOpenings();
  	virtual Direction move(GameState& state, int ms
#ifdef DEBUG
		, std::list<Direction>& moveSequence
#endif
  		);
	virtual void opponentMoved(Direction direction);
	virtual void reset();

  private:
  	const open::Move* move1_;
  	const open::Move* move2_;
  	const open::Move* move_;
  	Ai* mainAi_;
	bool initialized_;
};
	
} }

#endif