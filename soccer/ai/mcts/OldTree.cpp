#include "OldTree.h"
#include "../../Judge.h"
#include <algorithm>
#include <cmath>
#include <cstdio>

namespace soccer { namespace ai { namespace mcts {
	
OldTree::OldTree(Player me):
	wins_(0), plays_(0), me_(me)
{
	for(Direction i = 0; i < DIR_END; ++i)
		sons_[i] = nullptr;
}

OldTree::~OldTree()
{
	for(Direction i = 0; i < DIR_END; ++i)
		delete sons_[i];
}

void OldTree::playout(GameState& state, Ai* ai1, Ai* ai2)
{
	treePolicy_(state, ai1, ai2);
}

Direction OldTree::chooseMove()
{
	Direction bestMove = DIR_END;
	double bestValue = 0;
	for(Direction dir = 0; dir < DIR_END; ++dir)
	{
		if(!sons_[dir])
			continue;
		
		double value = sons_[dir]->getValue_(me_);
		if(sons_[dir]->isWinning_(me_) || value > bestValue || bestMove == DIR_END)
		{
			bestMove = dir;
			bestValue = value;
		}
	}
	return bestMove;
}

void OldTree::chooseMoveSequence(std::list<Direction>& moveSequence)
{
	printf("%u:\n", moveSequence.size());
	print();
	
	Direction bestMove = DIR_END;
	double bestValue = 0;
	for(Direction dir = 0; dir < DIR_END; ++dir)
	{
		if(!sons_[dir])
			continue;
		
		double value = sons_[dir]->getValue_(me_);
		if(sons_[dir]->isWinning_(me_) || value > bestValue || bestMove == DIR_END)
		{
			bestMove = dir;
			bestValue = value;
		}
	}
	
	if(bestMove == DIR_END)
		return;
	
	moveSequence.push_back(bestMove);
	sons_[bestMove]->chooseMoveSequence(moveSequence);
}

void OldTree::print()
{
	const char* DIRECTIONS[] = {"right", "up-right", "up", "up-left", "left", "down-left", "down", "down-right"};
	printf("root me: %u, wins: %u, plays: %u, value: %f\n", me_ == PLAYER_1 ? 1 : 2, wins_, plays_, getValue_(me_));
	for(Direction dir = 0; dir < DIR_END; ++dir)
	{
		if(sons_[dir])
		{
			printf("%s me: %u, wins: %u, plays: %u, value: %f, uct: %f\n", DIRECTIONS[dir], sons_[dir]->me_ == PLAYER_1 ? 1 : 2,
				sons_[dir]->wins_, sons_[dir]->plays_, sons_[dir]->getValue_(me_), sons_[dir]->getUct_(plays_, me_));
		}
	}
	printf("\n");
	fflush(stdout);
}

bool OldTree::treePolicy_(GameState& state, Ai* ai1, Ai* ai2)
{
	if(plays_ == -1)
		return wins_;
	
	if(state.isGameOver())
	{
		plays_ = -1;
		return wins_ = state.whoWon() == me_;
	}
	
	Direction direction = DIR_END;
	OldTree* son = chooseSon_(state, direction);
	bool win = false;
	if(son->plays_ >= n0)
		win = son->treePolicy_(state, ai1, ai2);
	else
		win = son->defaultPolicy_(state, ai1, ai2);
	
	if(son->plays_ == -1)
	{
		if(son->isWinning_(me_))
		{
			wins_ = 1;
			plays_ = -1;
			state.undo(direction);
			return true;
		}
		else
		{
			state.undo(direction);

			bool allLosing = true;
			for(Direction dir = 0; dir < DIR_END; ++dir)
			{
				if(!state.canMove(dir))
				   continue;
				
				if(!sons_[dir] || sons_[dir]->plays_ != -1 || sons_[dir]->isWinning_(me_))
				{
					allLosing = false;
					break;
				}
			}
			
			if(allLosing)
			{
				wins_ = 0;
				plays_ = -1;
				return false;
			}
			
			state.move(direction);
		}
	}
	
	win = win == (me_ == son->me_);
	wins_ += win;
	plays_ += 1;
	
	state.undo(direction);
	return win;
}

bool OldTree::defaultPolicy_(GameState& state, Ai* ai1, Ai* ai2)
{
	if(state.isGameOver())
	{
		wins_ = state.whoWon() == me_;
		plays_ = -1;
		return wins_;
	}
	
	bool won = Judge(ai1, ai2, state).run().whoWon() == me_;
	wins_ += won;
	plays_ += 1;
	return won;
}

OldTree* OldTree::chooseSon_(GameState& state, Direction& direction)
{
	Direction dirs[DIR_END];
	for(int i = 0; i < DIR_END; ++i)
		dirs[i] = i;
	std::random_shuffle(dirs, dirs + DIR_END);
	
	// TODO: wywalanie z dirs w tej petli
	for(int i = 0; i < DIR_END; ++i)
	{
		direction = dirs[i];
		
		if(!sons_[direction] && state.canMove(direction))
		{
			state.move(direction);
			return sons_[direction] = new OldTree(state.isGameOver() ? me_ : state.whoseTurn());
		}
	}
	
	direction = DIR_END;
	double bestUct = -INFINITY;
	OldTree* son = nullptr;
	for(int i = 0; i < DIR_END; ++i)
	{
		Direction dir = dirs[i];
		
		if(!state.canMove(dir))
			continue;
		
		double uct = sons_[dir]->getUct_(plays_, me_);
		if(uct > bestUct || direction == DIR_END)
		{
			son = sons_[dir];
			direction = dir;
			bestUct = uct;
		}
	}
	
	state.move(direction);
	return son;
}

bool OldTree::isWinning_(Player player) const
{
	return plays_ == -1 && (wins_ == 1) == (player == me_);
}

double OldTree::getValue_(Player player) const
{
	double value = ((double) wins_) / abs(plays_);
	return player == me_ ? value : 1 - value;
}

double OldTree::getUct_(int parentPlays, Player player) const
{
	return plays_ != -1 ? getValue_(player) + c * sqrt(log(parentPlays) / plays_) : -INFINITY;
}

int OldTree::n0 = 1;
double OldTree::c = 1;
	
} } }