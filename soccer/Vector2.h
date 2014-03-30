#ifndef _Soccer_Point_h_
#define _Soccer_Point_h_

#include "core.h"

namespace soccer {

struct Vector2
{
	int x, y;
	
	Vector2();
	Vector2(int x, int y);
	bool operator==(Vector2 that) const;
	bool operator!=(Vector2 that) const;
	Vector2 getNeighbor(Direction direction) const;
	bool isNeighbor(Vector2 point) const;	
	Direction getDirection(Vector2 neighbor) const;
};
	
}

#endif
