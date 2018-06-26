#ifndef _soccer_Tree_h_
#define _soccer_Tree_h_

#include "../../GameState.h"
#include "../../Ai.h"
#include "../../core.h"
#include <unordered_set>

namespace soccer { namespace ai { namespace mcts {
	
class Tree
{
  public:
  	Tree(Player me);
  	~Tree();
  	void playout(GameState& state, Ai* ai1, Ai* ai2);
  	Direction chooseMove();
  	void chooseMoveSequence(std::list<Direction>& moveSequence);
	//void print();
	bool isSolved() const;
	Tree* releaseSon(Direction direction);
	Tree* move(Direction direction);
	bool isWinning() const;
	Player getMe() const;
	void contribute(double* results);
  	
	static int n0;
  	static double c;
	static Heuristic heuristic;
	static double w;
	static double lambda;
	static double b;
	static int threads;
  
  private:
  	int treePolicy_(GameState& state, Ai* ai1, Ai* ai2,
  					 std::unordered_set<int>& moveCodes); // zwraca czy wygrana
  	int defaultPolicy_(GameState& state, Ai* ai1, Ai* ai2,
  						std::unordered_set<int>& moveCodes); // j.w.
  	Tree* chooseSon_(GameState& state, Direction& direction);
  	bool isWinning_(Player player) const;
  	double getValue_(Player player) const;
  	double getRaveValue_(Player player) const;
  	double getUct_(GameState& state, int parentPlays, Player player) const;
  	
  	int wins_;
  	int plays_;
  	int raveWins_;
  	int ravePlays_;
  	mutable double bias_;
  	Player me_;
  	Tree* sons_[DIR_END];
};
	
} } }

#endif