#ifndef _soccer_YourMove_h_
#define _soccer_YourMove_h_

#include "Move.h"
#include "../../core.h"
#include <memory>

namespace soccer { namespace ai { namespace open {
	
class YourMove: public Move
{
  public:
  	virtual bool isMyTurn() const;
  	void setMove(Direction direction, std::unique_ptr<Move> move);
    std::unique_ptr<Move> advance(Direction direction);
  	
  private:
    std::unique_ptr<Move> moves_[DIR_END];
};
	
} } }

#endif
