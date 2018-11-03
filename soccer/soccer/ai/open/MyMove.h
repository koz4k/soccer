#ifndef _soccer_MyMove_h_
#define _soccer_MyMove_h_

#include "Move.h"
#include "../../core.h"
#include <memory>

namespace soccer { namespace ai { namespace open {
	
class MyMove: public Move
{
  public:
  	MyMove(Direction direction, std::unique_ptr<Move> move);
  	virtual bool isMyTurn() const;
  	Direction getDirection() const;
    std::unique_ptr<Move> advance();
  	
  private:
  	Direction direction_;
    std::unique_ptr<Move> move_;
};
	
} } }

#endif
