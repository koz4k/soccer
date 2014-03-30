#ifndef _Soccer_GameState_h_
#define _Soccer_GameState_h_

#include "core.h"
#include <vector>

namespace soccer {
	
struct _Move;

class GameState
{
  public:
	class Field
	{
	  public:
		Field();
		bool isOccupied(Direction direction) const;
		bool couldRebound() const;
		bool isBlocked() const;
	
	  private:
	  	int getOccupiedCount_() const;
	  	Field& setOccupied_(Direction direction);
	  
		u8 links_;
		
		friend class GameState;
	};
	
	typedef _Move Move;

	GameState(int width, int height);
	const Field& getField(Point point) const;
	const Field& getCurrentField() const;
	Point getCurrentPosition() const;
	bool canMove(Direction direction) const;
	GameState& move(Direction direction);
	bool canRebound() const;
	bool isBlocked() const;
	std::vector<Move> getValidMoves() const; // TODO: optymalizacja
	bool isOnBorder(Point point, Direction direction) const;
	
  private:
	Field& getField_(Point point);
	Point boardToStorage_(Point board) const;
	void getValidMoves_(const std::vector<Direction>& prepend, 
						std::vector<Move>& acc) const;
	bool isOnBorder_(Point point) const;
						
	std::vector<Field> fields_;
	int width_, height_;
	Point currentPosition_;
};
	
struct _Move
{
	std::vector<Direction> sequence;
	GameState endState;
	
	_Move(std::vector<Direction>&& sequence, GameState&& endState);
};

}

#endif
