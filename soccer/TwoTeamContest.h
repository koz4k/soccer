#ifndef _Soccer_TwoTeamContest_h_
#define _Soccer_TwoTeamContest_h_

#include "Contest.h"

namespace soccer {

class TwoTeamContest: public Contest
{
  public:
  	TwoTeamContest(int separator, bool verbose = false);
};

}

#endif