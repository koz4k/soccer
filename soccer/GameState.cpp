#include "GameState.h"
#include <cmath>

namespace soccer {

inline GameState::Field::Field():
	links_(0)
{
}

inline bool GameState::Field::isOccupied(Direction direction) const
{
	return (links_ >> ((u8) direction)) & 1;
}

inline bool GameState::Field::couldRebound() const
{
	return links_ != 0;
}

inline bool GameState::Field::isBlocked() const
{
	return links_ == 0xff;
}

int GameState::Field::getOccupiedCount_() const
{
	int count = 0;
	for(u8 dir = (u8) DIR_BEGIN; dir < (u8) DIR_END; ++dir)
	{
		if((links_ >> dir) & 1)
			++count;
	}
	return count;
}

inline GameState::Field& GameState::Field::setOccupied_(Direction direction)
{
	links_ |= 1 << direction;
	return *this;
}

GameState::GameState(int width, int height):
	width_(width + 1), height_(height + 3), currentPosition_(0, 0)
{
	fields_.resize(width_ * height_);
		
	Vector2 p;
	for(p.x = -width / 2; p.x <= width / 2; ++p.x)
	{
		for(p.y = -height / 2 - 1; p.y <= height / 2 + 1; ++p.y)
		{
			if(!isOnBorder_(p))
				continue;
			
			for(Direction dir = DIR_BEGIN; dir < DIR_END; ++dir)
			{
				if(isOnBorder(p, dir))
					getField_(p).setOccupied_(dir);
			}
		}
	}
}
	
const GameState::Field& GameState::getField(Vector2 point) const
{
	point = boardToStorage_(point);
	return fields_[point.y * width_ + point.x];
}

inline const GameState::Field& GameState::getCurrentField() const
{
	return getField(currentPosition_);
}

Vector2 GameState::getCurrentPosition() const
{
	return currentPosition_;
}

inline bool GameState::canMove(Direction direction) const
{
	return !getCurrentField().isOccupied(direction);
}

GameState& GameState::move(Direction direction)
{
	getField_(currentPosition_).setOccupied_(direction);
	currentPosition_ = currentPosition_.getNeighbor(direction);
	getField_(currentPosition_).setOccupied_(reverseDirection(direction));
	return *this;
}

inline bool GameState::canRebound() const
{
	return getCurrentField().getOccupiedCount_() > 1;
}

bool GameState::isBlocked() const
{
	return getCurrentField().isBlocked();
}

bool GameState::isOnBorder(Vector2 point, Direction direction) const
{
	Vector2 point2 = point.getNeighbor(direction);
	if(!isOnBorder_(point) || !isOnBorder_(point2))
		return false;
	
	if(!(direction & 1))
		return true;
	
	Vector2 cross1(point.x, point2.y);
	Vector2 cross2(point2.x, point.y);
	return isOnBorder_(cross1) && isOnBorder_(cross2);
}
	
std::vector<GameState::Move> GameState::getValidMoves() const
{
	std::vector<Move> acc;
	getValidMoves_(std::vector<Direction>(), acc);
	return acc;
}

GameState::Field& GameState::getField_(Vector2 point)
{
	point = boardToStorage_(point);
	return fields_[point.y * width_ + point.x];
}
	
inline Vector2 GameState::boardToStorage_(Vector2 board) const
{
	return Vector2(board.x + (width_ - 1) / 2, board.y + (height_ - 1) / 2);
}

void GameState::getValidMoves_(const std::vector<Direction>& prepend,
							   std::vector<Move>& acc) const
{
	for(int dir = DIR_BEGIN; dir < DIR_END; ++dir)
	{
		if(canMove(dir))
		{
			GameState newState = *this;
			newState.move((Direction) dir);
			std::vector<Direction> sequence = prepend;
			sequence.push_back((Direction) dir);
			if(newState.canRebound())
				newState.getValidMoves_(sequence, acc);
			else
				acc.push_back(Move(std::move(sequence), std::move(newState)));
		}
	}
}

bool GameState::isOnBorder_(Vector2 point) const
{
	return std::abs(point.x) >= width_ / 2 ||
		   std::abs(point.y) >= height_ / 2 ||
		   (std::abs(point.y) == height_ / 2 - 1 && point.x);
}

inline _Move::_Move(std::vector<Direction>&& sequence, GameState&& endState):
	sequence(sequence), endState(endState)
{
}

}
