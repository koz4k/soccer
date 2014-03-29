#ifndef _Soccer_Point_h_
#define _Soccer_Point_h_

#include "core.h"

namespace soccer {

struct Point
{
	int x, y;
	
	Point();
	Point(int x, int y);
	bool operator==(Point that) const;
	bool operator!=(Point that) const;
	Point getNeighbor(Direction direction) const;
	bool isNeighbor(Point point) const;	
	Direction getDirection(Point neighbor) const;
};
	
}

#endif
