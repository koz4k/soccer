#ifndef _Soccer_FullContest_h_
#define _Soccer_FullContest_h_

#include "Contest.h"

namespace soccer {

class FullContest: public Contest
{
  public:
  	FullContest(bool fightSelf = false, bool verbose = false);
};
	
}

#endif
