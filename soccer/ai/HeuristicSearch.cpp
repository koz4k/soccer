#include "HeuristicSearch.h"

namespace soccer { namespace ai {

HeuristicSearch::HeuristicSearch(Heuristic heuristic):
	heuristic_(std::move(heuristic))
{
}
	
} }
