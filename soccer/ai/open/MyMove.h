#ifndef _Soccer_MyMove_h_
#define _Soccer_MyMove_h_

#include "Move.h"
#include "../../core.h"

namespace soccer { namespace ai { namespace open {
	
class MyMove: public Move
{
  public:
  	MyMove(Direction direction, const Move* move);
  	virtual ~MyMove();
  	virtual bool isMyTurn() const;
  	Direction getDirection() const;
  	const Move* advance() const;
  	
  private:
  	Direction direction_;
  	const Move* move_;
};
	
} } }

#endif