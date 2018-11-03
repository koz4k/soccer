#include "soccer/ai/AlphaBeta.h"
#include "soccer/ai/MaxSearch.h"
#include "soccer/ai/heur/naive.h"
#include "soccer/AiStandalone.h"

using namespace soccer;
using namespace ai;
using namespace heur;

int main()
{
	AiStandalone(std::make_unique<AlphaBeta>(naive1, 13)).run();
	return 0;
}