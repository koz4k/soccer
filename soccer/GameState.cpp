#include "GameState.h"
#include <cmath>

namespace soccer {

GameState::Field::Field():
	links_(0)
{
}

bool GameState::Field::isOccupied(Direction direction) const
{
	return direction >= DIR_BEGIN && direction < DIR_END ?
		   (links_ >> ((u8) direction)) & 1 : false;
}

bool GameState::Field::couldRebound() const
{
	return links_ != 0;
}

bool GameState::Field::isBlocked() const
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

GameState::Field& GameState::Field::setOccupied_(Direction direction, bool occupied)
{
	if(occupied)
		links_ |= 1 << direction;
	else
		links_ &= ~(1 << direction);
	return *this;
}

GameState::GameState(int width, int height):
	width_(width + 1), height_(height + 3), currentPosition_(0, 0), currentPlayer_(PLAYER_1),
	turnNumber_(0), moveNumber_(0), lastMoveCode_(-1)
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
	return fields_[boardToStorageIndex_(point)];
}

const GameState::Field& GameState::getCurrentField() const
{
	return getField(currentPosition_);
}

Vector2 GameState::getCurrentPosition() const
{
	return currentPosition_;
}

bool GameState::canMove(Direction direction) const
{
	return !getCurrentField().isOccupied(direction);
}

GameState& GameState::move(Direction direction)
{
	lastMoveCode_ = getMoveCode(direction);
	
	getField_(currentPosition_).setOccupied_(direction);
	currentPosition_ = currentPosition_.getNeighbor(direction);
	getField_(currentPosition_).setOccupied_(reverseDirection(direction));
	
	if(!canRebound() && !isBlocked())
	{
		currentPlayer_ = otherPlayer(currentPlayer_);
		
		if(currentPlayer_ == PLAYER_1)
			++turnNumber_;
	}
	
	++moveNumber_;
	
	return *this;
}

GameState& GameState::undo(Direction direction)
{
	lastMoveCode_ = -1;
	
	if(!canRebound() && !isBlocked())
	{
		if(currentPlayer_ == PLAYER_1)
			--turnNumber_;
		
		currentPlayer_ = otherPlayer(currentPlayer_);
	}
	
	direction = reverseDirection(direction);
	getField_(currentPosition_).setOccupied_(direction, false);
	currentPosition_ = currentPosition_.getNeighbor(direction);
	getField_(currentPosition_).setOccupied_(reverseDirection(direction), false);
	
	--moveNumber_;
	
	return *this;
}
	

bool GameState::canRebound() const
{
	return getCurrentField().getOccupiedCount_() > 1 && !isGameOver();
}

bool GameState::isBlocked() const
{
	return getCurrentField().isBlocked();
}

bool GameState::isGameOver() const
{
	return isBlocked() || std::abs(currentPosition_.y) == height_ / 2;
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

Player GameState::whoWon() const
{
	return currentPosition_.y == height_ / 2 ? PLAYER_1 :
		   currentPosition_.y == -height_ / 2 ? PLAYER_2 :
		   isBlocked() ? otherPlayer(currentPlayer_) : NO_PLAYER;
}

Player GameState::whoseTurn() const
{
	return currentPlayer_;
}

void GameState::setWhoseTurn(Player player)
{
	currentPlayer_ = player;
}

int GameState::whichTurn() const
{
	return turnNumber_;
}

int GameState::whichMove() const
{
	return moveNumber_;
}

int GameState::getMoveCode(Direction direction) const
{
	return (boardToStorageIndex_(currentPosition_) << 4) | (direction << 1) | // zahardcodowane z koniecznosci :(
		   ((int) currentPlayer_ == PLAYER_2);
}

int GameState::getLastMoveCode() const
{
	return lastMoveCode_;
}

GameState::Field& GameState::getField_(Vector2 point)
{
	return fields_[boardToStorageIndex_(point)];
}
	
Vector2 GameState::boardToStorage_(Vector2 board) const
{
	//return Vector2(board.x + (width_ - 1) / 2, board.y + (height_ - 1) / 2);
	Vector2 p(board.x + (width_ - 1) / 2, board.y + (height_ - 1) / 2);
	if(p.x < 0 || p.y < 0 || p.x >= width_ || p.y >= height_)
		throw 123;
	return p;
}

int GameState::boardToStorageIndex_(Vector2 board) const
{
	Vector2 point = boardToStorage_(board);
	return point.y * width_ + point.x;	
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

_Move::_Move(std::vector<Direction>&& sequence, GameState&& endState):
	sequence(sequence), endState(endState)
{
}

}