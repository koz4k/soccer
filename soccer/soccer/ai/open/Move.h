#ifndef _soccer_Move_h_
#define _soccer_Move_h_

namespace soccer { namespace ai { namespace open {
	
class Move
{
  public:
  	virtual ~Move() {}
  	virtual bool isMyTurn() const = 0;
};
	
} } }

#endif