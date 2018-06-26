#ifndef _soccer_TwoTeam_h_
#define _soccer_TwoTeam_h_

#include "../Contest.h"

namespace soccer { namespace contest {

class TwoTeam: public Contest
{
  public:
  	TwoTeam(int matchTime, int separator, bool verbose = false);
};

} }

#endif