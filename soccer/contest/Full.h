#ifndef _Soccer_Full_h_
#define _Soccer_Full_h_

#include "../Contest.h"

namespace soccer { namespace contest {

class Full: public Contest
{
  public:
  	Full(bool fightSelf = false, bool verbose = false);
};
	
} }

#endif