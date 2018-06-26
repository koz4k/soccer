#include "TwoTeam.h"

namespace soccer { namespace contest {

TwoTeam::TwoTeam(int matchTime, int separator, bool verbose):
	Contest([separator](int i, int j) { return (i < separator) != (j < separator); },
	matchTime, verbose)
{
}
	
} }