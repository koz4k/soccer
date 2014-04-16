#include "Board.h"
#include "conversion.h"

using namespace soccer;
using namespace Upp;

Board::Board():
	state_(DEFAULT_WIDTH, DEFAULT_HEIGHT), size_(DEFAULT_WIDTH, DEFAULT_HEIGHT),
	playerGate_(DEFAULT_HEIGHT / 2 + 1), aiGate_(-DEFAULT_HEIGHT / 2 - 1),
	moveBegin_(0, 0), target_(0, 0), freezed_(false), finished_(false)
{
}

Board& Board::Initialize(Size size, bool playerDown)
{
	state_ = GameState(size.cx, size.cy);
	size_ = size;
	
	playerGate_ = (playerDown ? -1 : 1) * (size.cy / 2 + 1);
	aiGate_ = -playerGate_;
	
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
		DrawLine_(draw, Vector2(x, -halfY), Vector2(x, halfY), 0, Gray());
	
	for(int y = -halfY; y <= halfY; ++y)
		DrawLine_(draw, Vector2(-halfX, y), Vector2(halfX, y), 0, Gray());

	DrawLine_(draw, Vector2(-1, -halfY), Vector2(1, -halfY), 2, White());
	DrawLine_(draw, Vector2(-halfX, -halfY + 1), Vector2(-1, -halfY + 1), 2, White());
	DrawLine_(draw, Vector2(1, -halfY + 1), Vector2(halfX, -halfY + 1), 2, White());

	DrawLine_(draw, Vector2(-1, halfY), Vector2(1, halfY), 2, White());
	DrawLine_(draw, Vector2(-halfX, halfY - 1), Vector2(-1, halfY - 1), 2, White());
	DrawLine_(draw, Vector2(1, halfY - 1), Vector2(halfX, halfY - 1), 2, White());
	
	DrawLine_(draw, Vector2(-1, -halfY), Vector2(-1, -halfY + 1), 2, White());
	DrawLine_(draw, Vector2(-halfX, -halfY + 1), Vector2(-halfX, halfY - 1), 2, White());
	DrawLine_(draw, Vector2(1, -halfY), Vector2(1, -halfY + 1), 2, White());
	
	DrawLine_(draw, Vector2(1, halfY), Vector2(1, halfY - 1), 2, White());
	DrawLine_(draw, Vector2(halfX, -halfY + 1), Vector2(halfX, halfY - 1), 2, White());
	DrawLine_(draw, Vector2(-1, halfY), Vector2(-1, halfY - 1), 2, White());
	
	/*std::vector<GameState::Move> validMoves = state_.getValidMoves();
	for(int i = 0; i < validMoves.size(); ++i)
	{
		Vector2 p;
		for(p.y = -halfY; p.y <= halfY; ++p.y)
		{
			for(p.x = -halfX; p.x <= halfX; ++p.x)
			{
				for(int dir = DIR_BEGIN; dir < DIR_END / 2; ++dir)
				{
					if(validMoves[i].endState.getField(p).isOccupied(dir) && !state_.isOnBorder(p, dir))
						DrawLine_(draw, p, p.getNeighbor(dir), 1, Red());
				}
			}
		}
	}*/
	
	Vector2 p;
	for(p.y = -halfY; p.y <= halfY; ++p.y)
	{
		for(p.x = -halfX; p.x <= halfX; ++p.x)
		{
			for(int dir = DIR_BEGIN; dir < DIR_END / 2; ++dir)
			{
				if(state_.getField(p).isOccupied(dir) && !state_.isOnBorder(p, dir))
					DrawLine_(draw, p, p.getNeighbor(dir), 1, White());
			}
		}
	}
	
	p = moveBegin_;
	for(int i = 0; i < move_.GetCount(); ++i)
	{
		Vector2 p2 = p.getNeighbor(move_[i]);
		DrawLine_(draw, p, p2, 2, White());
		p = p2;
	}
	
	DrawLine_(draw, p, target_, 2, White());
	
	DrawCircle_(draw, target_, 8, White());
}

void Board::MouseMove(Point point, dword)
{
	if(freezed_)
		return;
	
	Vector2 spoint = PixelToBoard_(point);
	Vector2 position = state_.getCurrentPosition();
	if(position.isNeighbor(spoint))
	{
		Direction direction = position.getDirection(spoint);
		if(state_.canMove(direction))
			target_ = spoint;
		else
			target_ = position;
	}
	else if(target_ != position)
		target_ = position;
	
	Refresh();
}

void Board::LeftDown(Point point, dword)
{
	if(freezed_)
		return;
	
	Vector2 spoint = PixelToBoard_(point);
	if(spoint != target_)
		return;

	Vector2 position = state_.getCurrentPosition();
	if(spoint == position)
		return;
	
	Direction direction = position.getDirection(spoint);
	if(state_.canMove(direction))
		state_.move(direction);
	
	WhenMove_(direction);

	if(state_.canRebound())
		move_.Add(direction);
	else
	{
		moveBegin_ = target_;
		move_.Clear();
		
		WhenFullMove_();
		moveBegin_ = target_ = state_.getCurrentPosition();
	}
	
	Refresh();
}

Point Board::BoardToPixel_(Vector2 point)
{	
	// TODO: do skladowych prywatnych
	
	Size pixelSize = GetSize();
	double tile = min(((double) pixelSize.cx - 32) / size_.cx,
	    			  ((double) pixelSize.cy - 32) / (size_.cy + 2));

	Size fullSize = size_ + Size(0, 2);
	Size fieldSize = tile * fullSize;
	Point center = pixelSize / 2;
	Point start = center - fieldSize / 2;
	
	// TODO: skorzystac z Vector2
	
	Point upoint = ConvertVector(point);
	
	upoint.y *= -1;
	upoint += fullSize / 2;
	upoint *= tile;
	upoint += start;
	
	return upoint;
}

Vector2 Board::PixelToBoard_(Point point)
{
	// TODO: do skladowych prywatnych
	
	Size pixelSize = GetSize();
	double tile = min(((double) pixelSize.cx - 32) / size_.cx,
	    			  ((double) pixelSize.cy - 32) / (size_.cy + 2));

	Size fullSize = size_;
	Size fieldSize = tile * fullSize;
	Point center = pixelSize / 2;
	Point start = center - fieldSize / 2;
	
	// TODO: skorzystac z Vector2
	
	point -= start;
	point.x = (int) round(((double) point.x) / tile);
	point.y = (int) round(((double) point.y) / tile);
	point -= fullSize / 2;
	point.y *= -1;
	return ConvertVector(point);
}

void Board::DrawLine_(Draw& draw, Vector2 from, Vector2 to, int width, Color color)
{
	Point ufrom = BoardToPixel_(from);
	Point uto = BoardToPixel_(to);
	draw.DrawLine(ufrom.x, ufrom.y, uto.x, uto.y, width, color);
}

void Board::DrawCircle_(Draw& draw, Vector2 center, int radius, Color color)
{
	Point ucenter = BoardToPixel_(center);
	draw.DrawEllipse(ucenter.x - radius / 2, ucenter.y - radius / 2, radius, radius, color);
}

void Board::WhenMove_(Direction direction)
{
	if(finished_)
		return;
	
	Vector2 position = state_.getCurrentPosition();
	if(position.y == aiGate_)
		WhenGameOver_(true);
	else if(position.y == playerGate_ || state_.isBlocked())
		WhenGameOver_(false);
	else
		WhenMove(state_, direction);
}

void Board::WhenFullMove_()
{
	if(finished_)
		return;

	Freeze();
	
	WhenFullMove(state_);
	
	Unfreeze();
	
	if(state_.getCurrentPosition().y == playerGate_)
		WhenGameOver_(false);
	else if(state_.getCurrentPosition().y == aiGate_ || state_.isBlocked())
		WhenGameOver_(true);
}

void Board::WhenGameOver_(bool won)
{
	Freeze();
	finished_ = true;
	WhenGameOver(state_, won);
}
