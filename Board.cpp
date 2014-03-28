#include "Board.h"

using namespace Upp;

Board::Board(): size_(8, 10)
{
}

void Board::SetBoardSize(Size size)
{
	size_ = size;
}

void Board::Paint(Draw& draw)
{
	draw.DrawRect(GetSize(), Green());
	
	Size pixelSize = GetSize();
	double tile = min(((double) pixelSize.cx - 32) / size_.cx,
	    			  ((double) pixelSize.cy - 32) / (size_.cy + 2));
	
	Size fullSize = size_ + Size(0, 2);
	Size fieldSize = tile * fullSize;
	Point center = pixelSize / 2;
	Point start = center - fieldSize / 2;
	Point end = start + fieldSize;
	
	for(int x = 0; x <= fullSize.cx; ++x)
		draw.DrawLine(start.x + x * tile, start.y, start.x + x * tile, end.y, 0, Gray());
	
	for(int y = 0; y <= fullSize.cy; ++y)
		draw.DrawLine(start.x, start.y + y * tile, end.x, start.y + y * tile, 0, Gray());
	
	draw.DrawLine(start.x, start.y + tile, center.x - tile, start.y + tile, 2, White());
	draw.DrawLine(center.x + tile, start.y + tile, end.x, start.y + tile, 2, White());
	draw.DrawLine(start.x, end.y - tile, center.x - tile, end.y - tile, 2, White());
	draw.DrawLine(center.x + tile, end.y - tile, end.x, end.y - tile, 2, White());
	
	draw.DrawLine(start.x, start.y + tile, start.x, end.y - tile, 2, White());
	draw.DrawLine(end.x, start.y + tile, end.x, end.y - tile, 2, White());
	
	draw.DrawLine(center.x - tile, start.y, center.x + tile, start.y, 2, White());
	draw.DrawLine(center.x - tile, end.y, center.x + tile, end.y, 2, White());
	
	draw.DrawLine(center.x - tile, start.y, center.x - tile, start.y + tile, 2, White());
	draw.DrawLine(center.x + tile, start.y, center.x + tile, start.y + tile, 2, White());
	draw.DrawLine(center.x - tile, end.y, center.x - tile, end.y - tile, 2, White());
	draw.DrawLine(center.x + tile, end.y, center.x + tile, end.y - tile, 2, White());
	
	draw.DrawEllipse(center.x - 4, center.y - 4, 8, 8, White());
}

void Board::LeftDown(Point, dword)
{
}