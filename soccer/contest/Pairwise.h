#ifndef _Soccer_Pairwise_h_
#define _Soccer_Pairwise_h_

#include "../Contest.h"

namespace soccer { namespace contest {

class Pairwise: public Contest
{
  public:
  	Pairwise(bool dense = false, bool verbose = false);
};

} }

#endif