#ifndef _Soccer_Tree_h_
#define _Soccer_Tree_h_

#include "../../GameState.h"
#include "../../Ai.h"

namespace soccer { namespace ai { namespace mcts {
	
class Tree
{
  public:
  	Tree(Player me);
  	~Tree();
  	void playout(GameState& state, Ai* ai1, Ai* ai2);
  	Direction chooseMove();
  	void chooseMoveSequence(std::list<Direction>& moveSequence);
	void print();
  	
	static int n0;
  	static double c;
  
  private:
  	bool treePolicy_(GameState& state, Ai* ai1, Ai* ai2); // zwraca czy wygrana
  	bool defaultPolicy_(GameState& state, Ai* ai1, Ai* ai2); // j.w.
  	Tree* chooseSon_(GameState& state, Direction& direction);
  	bool isWinning_(Player player) const;
  	double getValue_(Player player) const;
  	double getUct_(int parentPlays, Player player) const;
  	
  	int wins_;
  	int plays_;
  	Player me_;
  	Tree* sons_[DIR_END];
};
	
} } }

#endif