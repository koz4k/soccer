#include "conversion.h"

Upp::Point ConvertVector(soccer::Vector2 point)
{
	return Upp::Point(point.x, point.y);
}

soccer::Vector2 ConvertVector(Upp::Point point)
{
	return soccer::Vector2(point.x, point.y);
}
