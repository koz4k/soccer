#include "Full.h"

namespace soccer { namespace contest {

Full::Full(int matchTime, bool fightSelf, bool verbose):
	Contest([fightSelf](int i, int j) { return i != j ? true : fightSelf; }, matchTime, verbose)
{
}

} }