#include "upp.h"

namespace soccer {

Upp::Point pointToUpp(Point point)
{
	return Upp::Point(point.x, point.y);
}

Point pointFromUpp(Upp::Point point)
{
	return Point(point.x, point.y);
}
	
}
