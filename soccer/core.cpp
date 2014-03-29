#include "core.h"

namespace soccer {

Direction reverseDirection(Direction direction)
{
	return (direction + DIR_END / 2) % DIR_END;
}
	
}
