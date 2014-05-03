#include "TwoTeamContest.h"

namespace soccer {

TwoTeamContest::TwoTeamContest(int separator, bool verbose):
	Contest([separator](int i, int j) { return (i < separator) != (j < separator); }, verbose)
{
}
	
}