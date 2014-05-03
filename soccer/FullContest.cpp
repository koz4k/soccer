#include "FullContest.h"

namespace soccer {

FullContest::FullContest(bool fightSelf, bool verbose):
	Contest([fightSelf](int i, int j) { return i != j ? true : fightSelf; }, verbose)
{
}
	
}