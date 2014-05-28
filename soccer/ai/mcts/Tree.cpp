#include "Tree.h"
#include "../../Judge.h"
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <cassert>

namespace soccer { namespace ai { namespace mcts {
	
Tree::Tree(Player me):
	wins_(0), plays_(0), raveWins_(0), ravePlays_(0), bias_(NAN), me_(me)
{
	srand(time(nullptr));
	
	for(Direction i = 0; i < DIR_END; ++i)
		sons_[i] = nullptr;
}

Tree::~Tree()
{
	for(Direction i = 0; i < DIR_END; ++i)
		delete sons_[i];
}

void Tree::playout(GameState& state, Ai* ai1, Ai* ai2)
{
	std::unordered_set<int> moveCodes;
	treePolicy_(state, ai1, ai2, moveCodes);
}

Direction Tree::chooseMove()
{
	Direction bestMove = DIR_END;
	double bestValue = -INFINITY;
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

void Tree::chooseMoveSequence(std::list<Direction>& moveSequence)
{
	//printf("%u:\n", moveSequence.size());
	//print();
	
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

/*void Tree::print()
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
}*/

bool Tree::isSolved() const
{
	return plays_ == -1;
}

Tree* Tree::releaseSon(Direction direction)
{
	Tree* son = nullptr;
	std::swap(son, sons_[direction]);
	return son;
}

Tree* Tree::move(Direction direction)
{
	Tree* son = releaseSon(direction);
	delete this;
	return son;
}

bool Tree::isWinning() const
{
	return isWinning_(me_);
}

Player Tree::getMe() const
{
	return me_;
}

void Tree::contribute(double* results)
{
	for(Direction dir = 0; dir < DIR_END; ++dir)
		results[dir] += sons_[dir] ? sons_[dir]->getValue_(me_) : 0;
}

int Tree::treePolicy_(GameState& state, Ai* ai1, Ai* ai2, std::unordered_set<int>& moveCodes)
{
	if(plays_ == -1)
		return wins_;
	
	if(state.isGameOver())
	{
		plays_ = -1;
		return wins_ = state.whoWon() == me_;
	}
	
Vector2 p = state.getCurrentPosition();
	
	Direction direction = DIR_END;
	Tree* son = chooseSon_(state, direction);
	/*state.undo(direction);
	moveCodes.insert(state.getMoveCode(direction));
	state.move(direction);*/
	int win = 0;
	if(son->plays_ >= n0)
		win = son->treePolicy_(state, ai1, ai2, moveCodes);
	else
		win = son->defaultPolicy_(state, ai1, ai2, moveCodes);
	
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
	
	win = me_ == son->me_ ? win : !win;
	//win = win == (me_ == son->me_);
	wins_ += win;
	plays_ += 1;
	
	state.undo(direction);
	
	assert(state.getCurrentPosition() == p);
	
	/*for(Direction dir = DIR_BEGIN; dir < DIR_END; ++dir)
	{
		if(!sons_[dir])
			continue;
		
		int code = state.getMoveCode(dir);
		if(moveCodes.find(code) != moveCodes.end()) // to dziala, bo kody zawieraja informacje o graczu ktory wykonuje ruch
		{
			sons_[dir]->raveWins_ += win;
			sons_[dir]->ravePlays_ += 1;
		}
	}*/
	
	return win;
}

int Tree::defaultPolicy_(GameState& state, Ai* ai1, Ai* ai2, std::unordered_set<int>& moveCodes)
{
	if(state.isGameOver())
	{
		plays_ = -1;
		return wins_ = state.whoWon() == me_;
	}
	
	/*Judge judge(ai1, ai2, state);
	while(!judge.getGameState().isGameOver())
		moveCodes.insert(judge.oneMove().getLastMoveCode());*/
	
	wins_ += Judge(ai1, ai2, state).run().whoWon() == me_;
	plays_ += 1;
	return wins_;
}

Tree* Tree::chooseSon_(GameState& state, Direction& direction)
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
			return sons_[direction] = new Tree(state.isGameOver() ? me_ : state.whoseTurn());
		}
	}
	
	direction = DIR_END;
	double bestUct = -INFINITY;
	Tree* son = nullptr;
	for(int i = 0; i < DIR_END; ++i)
	{
		Direction dir = dirs[i];
		
		if(!state.canMove(dir))
			continue;
		
		double uct = sons_[dir]->getUct_(state, plays_, me_);
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

bool Tree::isWinning_(Player player) const
{
	return plays_ == -1 && (wins_ == 1) == (player == me_);
}

double Tree::getValue_(Player player) const
{
	double value = ((double) wins_) / abs(plays_);
	return player == me_ ? value : 1 - value;
}

double Tree::getRaveValue_(Player player) const
{
	double value = ((double) raveWins_) / abs(ravePlays_);
	return player == me_ ? value : 1 - value;
}

double Tree::getUct_(GameState& state, int parentPlays, Player player) const
{
	if(isnan(bias_))
		bias_ = w / (1 + exp(-lambda * heuristic(state)));
	/*double beta = ravePlays_ / (plays_ + ravePlays_ + 4 * b * b * plays_ * ravePlays_);
	if(plays_ != -1)
	{
		printf("beta: %f, rave: %f\n", beta, getRaveValue_(player));
		fflush(stdout);
	}*/
	/*return plays_ != -1 ? (1 - beta) * getValue_(player) + beta * getRaveValue_(player) +
		   c * sqrt(log(parentPlays) / plays_) + bias_ / (plays_ - wins_ + 1) : -INFINITY;*/
	return plays_ != -1 ? getValue_(player) +
		   c * sqrt(log(parentPlays) / plays_) + bias_ / (plays_ - wins_ + 1) : -INFINITY;
}

int Tree::n0 = 1;
double Tree::c = 1;
double Tree::w = 0;
double Tree::lambda = 1;
Heuristic Tree::heuristic;
double Tree::b = 1000000000;
	
} } }