#include "soccer/ai/open/AlphaBetaGenerator.h"
#include "soccer/ai/open/io.h"
#include "soccer/ai/heur/naive.h"
#include <memory>
#include <cmath>

using namespace soccer;
using namespace ai;
using namespace heur;
using namespace open;

int main(int argc, char* argv[])
{
	int depth = 1, limit = 1, confidence1 = 12, confidence2 = 12;
	const char* out1 = "openings1";
	const char* out2 = "openings2";
	if(argc > 4)
	{
		depth = atoi(argv[1]);
		limit = atoi(argv[2]);
		confidence1 = atoi(argv[3]);
		confidence2 = atoi(argv[4]);
		out1 = argv[5];
		out2 = argv[6];
	}
	
	AlphaBetaGenerator gen(depth, limit, naive1);
    std::unique_ptr<Move> openings1 = gen.generate(true, confidence1);
    std::unique_ptr<Move> openings2 = gen.generate(false, confidence2);
	save(std::move(openings1), out1);
	save(std::move(openings2), out2);
	
	return 0;
}
