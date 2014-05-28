#ifndef _Soccer_AlphaBeta_h_
#define _Soccer_AlphaBeta_h_

#include "HeuristicSearch.h"

namespace soccer { namespace ai {

class AlphaBeta: public HeuristicSearch
{
  public:
  	AlphaBeta(Heuristic heuristic, int maxDepth);
  	virtual Direction move(GameState& state, int ms
#ifdef DEBUG
		, std::list<Direction>& moveSequence
#endif
  		);
  	void setDepth(int depth);
  
  private:
  	double alphaBeta_(GameState& state, int color, int depth,
  					  double alpha, double beta, Direction& move
#ifdef DEBUG
  					, std::list<Direction>& sequence
#endif
  				   );
  
  	int maxDepth_;
};
	
} }

#endif