#include "Vector2.h"
#include <cmath>

namespace soccer {

Vector2::Vector2(): x(0), y(0)
{
}

Vector2::Vector2(int x, int y):
	x(x), y(y)
{
}

bool Vector2::operator==(Vector2 that) const
{
	return x == that.x && y == that.y;
}

bool Vector2::operator!=(Vector2 that) const
{
	return x != that.x || y != that.y;
}

Vector2 Vector2::getNeighbor(Direction direction) const
{
	switch(direction)
	{
	  case DIR_UP:
	  	return Vector2(x, y + 1);
	  	
	  case DIR_UP_RIGHT:
	  	return Vector2(x + 1, y + 1);
	  	
	  case DIR_RIGHT:
	  	return Vector2(x + 1, y);
	  	
	  case DIR_DOWN_RIGHT:
	  	return Vector2(x + 1, y - 1);
	  	
	  case DIR_DOWN:
	  	return Vector2(x, y - 1);
	  	
	  case DIR_DOWN_LEFT:
	  	return Vector2(x - 1, y - 1);
	  	
	  case DIR_LEFT:
	  	return Vector2(x - 1, y);
	  	
	  case DIR_UP_LEFT:
	  	return Vector2(x - 1, y + 1);
	  
	  default:
	  	return *this;
	}
}

bool Vector2::isNeighbor(Vector2 point) const
{
	return std::abs(x - point.x) <= 1 && std::abs(y - point.y) <= 1 &&
		   (x != point.x || y != point.y);
}

inline int sgn(int x)
{
	return x > 0 ? 1 : x < 0 ? -1 : 0;
}

Direction Vector2::getDirection(Vector2 neighbor) const
{
	switch(sgn(neighbor.x - x))
	{
	  case 1:
	  	switch(sgn(neighbor.y - y))
	  	{
	  	  case 1:
	  	  	return DIR_UP_RIGHT;
	  	  
	  	  case 0:
	  	  	return DIR_RIGHT;
	  	  	
	  	  case -1:
	  	  	return DIR_DOWN_RIGHT;
	  	}
	  	
	  case 0:
	  	return neighbor.y > y ? DIR_UP : DIR_DOWN;
	  	
	  case -1:
	  	switch(sgn(neighbor.y - y))
	  	{
	  	  case 1:
	  	  	return DIR_UP_LEFT;
	  	  	
	  	  case 0:
	  	  	return DIR_LEFT;
	  	  	
	  	  case -1:
	  	  	return DIR_DOWN_LEFT;
	  	}
	}
}
	
}
