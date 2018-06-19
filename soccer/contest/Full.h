#ifndef _soccer_Full_h_
#define _soccer_Full_h_

#include "../Contest.h"

namespace soccer { namespace contest {

class Full: public Contest
{
  public:
  	Full(int matchTime, bool fightSelf = false, bool verbose = false);
};
	
} }

#endif