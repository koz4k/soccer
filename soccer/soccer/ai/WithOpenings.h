#ifndef _soccer_WithOpenings_h_
#define _soccer_WithOpenings_h_

#include "../Ai.h"
#include "open/Move.h"
#include <memory>

namespace soccer { namespace ai {

class WithOpenings: public Ai
{
  public:
  	WithOpenings(const std::string& file1, const std::string& file2, std::unique_ptr<Ai> mainAi);
  	virtual Direction move(GameState& state, int ms
#ifdef DEBUG
		, std::list<Direction>& moveSequence
#endif
  		);
	virtual void opponentMoved(Direction direction);
	virtual void reset();

  private:
    std::unique_ptr<open::Move> move1_;
    std::unique_ptr<open::Move> move2_;
    std::unique_ptr<open::Move> move_;
    std::unique_ptr<Ai> mainAi_;
	bool initialized_;
};
	
} }

#endif
