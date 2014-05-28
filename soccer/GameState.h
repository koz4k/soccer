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

	explicit GameState(int width = 8, int height = 10);
	const Field& getField(Vector2 point) const;
	const Field& getCurrentField() const;
	Vector2 getCurrentPosition() const;
	bool canMove(Direction direction) const;
	virtual GameState& move(Direction direction);
	virtual GameState& undo(Direction direction);
	bool canRebound() const;
	bool isBlocked() const;
	bool isGameOver() const;
	std::vector<Move> getValidMoves() const; // TODO: optymalizacja
	bool isOnBorder(Vector2 point, Direction direction) const;
	Player whoseTurn() const;
	void setWhoseTurn(Player player);
	Player whoWon() const;
	int whichTurn() const;
	int whichMove() const;
	int getMoveCode(Direction direction) const;
	int getLastMoveCode() const;
	
  protected:
	Field& getField_(Vector2 point);
	
  private:
	Vector2 boardToStorage_(Vector2 board) const;
	int boardToStorageIndex_(Vector2 board) const;
	void getValidMoves_(const std::vector<Direction>& prepend, 
						std::vector<Move>& acc) const;
	bool isOnBorder_(Vector2 point) const;
						
	std::vector<Field> fields_;
	int width_, height_;
	Vector2 currentPosition_;
	Player currentPlayer_;
	int turnNumber_;
	int moveNumber_;
	int lastMoveCode_;
};
	
struct _Move
{
	std::vector<Direction> sequence;
	GameState endState;
	
	_Move(std::vector<Direction>&& sequence, GameState&& endState);
};

}

#endif