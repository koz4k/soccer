#ifndef _Soccer_YourMove_h_
#define _Soccer_YourMove_h_

#include "Move.h"
#include "../../core.h"

namespace soccer { namespace ai { namespace open {
	
class YourMove: public Move
{
  public:
  	YourMove();
  	virtual ~YourMove();
  	virtual bool isMyTurn() const;
  	void setMove(Direction direction, const Move* move);
  	const Move* advance(Direction direction) const;
  	
  private:
  	const Move* moves_[DIR_END];
};
	
} } }

#endif