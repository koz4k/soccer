#include "Pairwise.h"

namespace soccer { namespace contest {

Pairwise::Pairwise(int matchTime, bool dense, bool verbose):
	Contest([dense](int i, int j) -> bool { return dense ? std::abs(i - j) == 1 :
											  		       !(i >> 1 ^ j >> 1) && i ^ j; },
			matchTime, verbose)
{
}

} }