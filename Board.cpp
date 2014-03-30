#include "Board.h"
#include "soccer/upp.h"

using namespace Upp;

Board::Board():
	state_(soccer::DEFAULT_WIDTH, soccer::DEFAULT_HEIGHT),
	size_(soccer::DEFAULT_WIDTH, soccer::DEFAULT_HEIGHT),
	moveBegin_(0, 0), target_(0, 0), freezed_(false)
{
}

Board& Board::SetBoardSize(Size size)
{
	state_ = soccer::GameState(size.cx, size.cy);
	size_ = size;
	
	return *this;
}

Board& Board::Freeze()
{
	freezed_ = true;
	
	return *this;
}

Board& Board::Unfreeze()
{
	freezed_ = false;
	
	return *this;
}

void Board::Paint(Draw& draw)
{
	draw.DrawRect(GetSize(), Green());
	
	int halfX = size_.cx / 2, halfY = size_.cy / 2 + 1;
	
	for(int x = -halfX; x <= halfX; ++x)
		DrawLine_(draw, Point(x, -halfY), Point(x, halfY), 0, Gray());
	
	for(int y = -halfY; y <= halfY; ++y)
		DrawLine_(draw, Point(-halfX, y), Point(halfX, y), 0, Gray());

	DrawLine_(draw, Point(-1, -halfY), Point(1, -halfY), 2, White());
	DrawLine_(draw, Point(-halfX, -halfY + 1), Point(-1, -halfY + 1), 2, White());
	DrawLine_(draw, Point(1, -halfY + 1), Point(halfX, -halfY + 1), 2, White());

	DrawLine_(draw, Point(-1, halfY), Point(1, halfY), 2, White());
	DrawLine_(draw, Point(-halfX, halfY - 1), Point(-1, halfY - 1), 2, White());
	DrawLine_(draw, Point(1, halfY - 1), Point(halfX, halfY - 1), 2, White());
	
	DrawLine_(draw, Point(-1, -halfY), Point(-1, -halfY + 1), 2, White());
	DrawLine_(draw, Point(-halfX, -halfY + 1), Point(-halfX, halfY - 1), 2, White());
	DrawLine_(draw, Point(1, -halfY), Point(1, -halfY + 1), 2, White());
	
	DrawLine_(draw, Point(1, halfY), Point(1, halfY - 1), 2, White());
	DrawLine_(draw, Point(halfX, -halfY + 1), Point(halfX, halfY - 1), 2, White());
	DrawLine_(draw, Point(-1, halfY), Point(-1, halfY - 1), 2, White());
	
	soccer::Point p;
	for(p.y = -halfY; p.y <= halfY; ++p.y)
	{
		for(p.x = -halfX; p.x <= halfX; ++p.x)
		{
			for(int dir = soccer::DIR_BEGIN; dir < soccer::DIR_END / 2; ++dir)
			{
				if(state_.getField(p).isOccupied(dir) && !state_.isOnBorder(p, dir))
					DrawLine_(draw, pointToUpp(p),
							  pointToUpp(p.getNeighbor(dir)), 1, White());
			}
		}
	}
	
	p = soccer::pointFromUpp(moveBegin_);
	for(int i = 0; i < move_.GetCount(); ++i)
	{
		soccer::Point p2 = p.getNeighbor(move_[i]);
		DrawLine_(draw, soccer::pointToUpp(p), soccer::pointToUpp(p2), 2, White());
		p = p2;
	}
	
	DrawLine_(draw, soccer::pointToUpp(p), target_, 2, White());
	
	DrawCircle_(draw, target_, 8, White());
}

void Board::MouseMove(Point point, dword)
{
	if(freezed_)
		return;
	
	soccer::Point spoint = soccer::pointFromUpp(PixelToBoard_(point));
	soccer::Point position = state_.getCurrentPosition();
	if(position.isNeighbor(spoint))
	{
		soccer::Direction direction = position.getDirection(spoint);
		if(state_.canMove(direction))
		{
			target_ = pointToUpp(spoint);
		}
		else
			target_ = pointToUpp(position);
	}
	else if(target_ != pointToUpp(position))
		target_ = pointToUpp(position);
	
	Refresh();
}

void Board::LeftDown(Point point, dword)
{
	if(freezed_)
		return;
	
	point = PixelToBoard_(point);
	if(point != target_)
		return;

	soccer::Point spoint = soccer::pointFromUpp(point);
	soccer::Point position = state_.getCurrentPosition();
	if(spoint == position)
		return;
	
	soccer::Direction direction = position.getDirection(spoint);
	if(state_.canMove(direction))
		state_.move(direction);
	
	WhenMove(state_, direction);

	if(state_.canRebound())
		move_.Add(direction);
	else
	{
		moveBegin_ = target_;
		move_.Clear();
		
		WhenFullMove(state_);
		moveBegin_ = target_ = soccer::pointToUpp(state_.getCurrentPosition());
	}
	
	Refresh();
}

Point Board::BoardToPixel_(Point point)
{
	// TODO: do skladowych prywatnych
	
	Size pixelSize = GetSize();
	double tile = min(((double) pixelSize.cx - 32) / size_.cx,
	    			  ((double) pixelSize.cy - 32) / (size_.cy + 2));

	Size fullSize = size_ + Size(0, 2);
	Size fieldSize = tile * fullSize;
	Point center = pixelSize / 2;
	Point start = center - fieldSize / 2;
	
	point.y *= -1;
	point += fullSize / 2;
	point *= tile;
	point += start;
	return point;
}

Upp::Point Board::PixelToBoard_(Upp::Point point)
{
	// TODO: do skladowych prywatnych
	
	Size pixelSize = GetSize();
	double tile = min(((double) pixelSize.cx - 32) / size_.cx,
	    			  ((double) pixelSize.cy - 32) / (size_.cy + 2));

	Size fullSize = size_;
	Size fieldSize = tile * fullSize;
	Point center = pixelSize / 2;
	Point start = center - fieldSize / 2;
	
	point -= start;
	point.x = (int) round(((double) point.x) / tile);
	point.y = (int) round(((double) point.y) / tile);
	point -= fullSize / 2;
	point.y *= -1;
	return point;
}

void Board::DrawLine_(Draw& draw, Point from, Point to, int width, Color color)
{
	from = BoardToPixel_(from);
	to = BoardToPixel_(to);
	draw.DrawLine(from.x, from.y, to.x, to.y, width, color);
}

void Board::DrawCircle_(Draw& draw, Point center, int radius, Color color)
{
	center = BoardToPixel_(center);
	draw.DrawEllipse(center.x - radius / 2, center.y - radius / 2, radius, radius, color);
}
