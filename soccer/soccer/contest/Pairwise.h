#ifndef _soccer_Pairwise_h_
#define _soccer_Pairwise_h_

#include "../Contest.h"

namespace soccer { namespace contest {

class Pairwise: public Contest
{
  public:
  	Pairwise(int matchTime, bool dense = false, bool verbose = false);
};

} }

#endif