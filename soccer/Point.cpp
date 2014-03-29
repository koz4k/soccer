#include "Point.h"
#include <cmath>

namespace soccer {

Point::Point(): x(0), y(0)
{
}

Point::Point(int x, int y):
	x(x), y(y)
{
}

bool Point::operator==(Point that) const
{
	return x == that.x && y == that.y;
}

bool Point::operator!=(Point that) const
{
	return x != that.x || y != that.y;
}

Point Point::getNeighbor(Direction direction) const
{
	switch(direction)
	{
	  case DIR_UP:
	  	return Point(x, y + 1);
	  	
	  case DIR_UP_RIGHT:
	  	return Point(x + 1, y + 1);
	  	
	  case DIR_RIGHT:
	  	return Point(x + 1, y);
	  	
	  case DIR_DOWN_RIGHT:
	  	return Point(x + 1, y - 1);
	  	
	  case DIR_DOWN:
	  	return Point(x, y - 1);
	  	
	  case DIR_DOWN_LEFT:
	  	return Point(x - 1, y - 1);
	  	
	  case DIR_LEFT:
	  	return Point(x - 1, y);
	  	
	  case DIR_UP_LEFT:
	  	return Point(x - 1, y + 1);
	  
	  default:
	  	return *this;
	}
}

bool Point::isNeighbor(Point point) const
{
	return std::abs(x - point.x) <= 1 && std::abs(y - point.y) <= 1 &&
		   (x != point.x || y != point.y);
}

inline int sgn(int x)
{
	return x > 0 ? 1 : x < 0 ? -1 : 0;
}

Direction Point::getDirection(Point neighbor) const
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
