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
	  	Field& setOccupied_(Direction direction, bool occupied = true);
	  
		u8 links_;
		
		friend class GameState;
	};
	
	typedef _Move Move;

	GameState(int width = 10, int height = 8);
	const Field& getField(Vector2 point) const;
	const Field& getCurrentField() const;
	Vector2 getCurrentPosition() const;
	bool canMove(Direction direction) const;
	GameState& move(Direction direction);
	GameState& undo(Direction direction);
	bool canRebound() const;
	bool isBlocked() const;
	bool isGameOver() const;
	std::vector<Move> getValidMoves() const; // TODO: optymalizacja
	bool isOnBorder(Vector2 point, Direction direction) const;
	Player whoseTurn() const;
	Player whoWon() const;
	
  private:
	Field& getField_(Vector2 point);
	Vector2 boardToStorage_(Vector2 board) const;
	void getValidMoves_(const std::vector<Direction>& prepend, 
						std::vector<Move>& acc) const;
	bool isOnBorder_(Vector2 point) const;
						
	std::vector<Field> fields_;
	int width_, height_;
	Vector2 currentPosition_;
	Player currentPlayer_;
};
	
struct _Move
{
	std::vector<Direction> sequence;
	GameState endState;
	
	_Move(std::vector<Direction>&& sequence, GameState&& endState);
};

}

#endif
