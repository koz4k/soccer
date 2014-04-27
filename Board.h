#ifndef _Soccer_Board_h_
#define _Soccer_Board_h_

#include <CtrlLib/CtrlLib.h>
#include "soccer/GameState.h"

class Board: public Upp::Ctrl
{
  public:
	Board();
	Board& Initialize(Upp::Size size);
	Board& Freeze();
	Board& Unfreeze();
	soccer::GameState& GetGameState();
	void AddDebugLine(soccer::Vector2 p1, soccer::Vector2 p2, Upp::Color color);
	void ClearDebug();
	virtual void Paint(Upp::Draw& w);
	virtual void MouseMove(Upp::Point point, Upp::dword);
	virtual void LeftDown(Upp::Point, Upp::dword);

	Upp::Callback2<const soccer::GameState&, soccer::Direction> WhenMove;
	Upp::Callback1<soccer::GameState&> WhenFullMove;
	Upp::Callback1<const soccer::GameState&> WhenGameOver;
	
  private:
  
  	struct DebugLine_
  	{
  		soccer::Vector2 p1, p2;
  		Upp::Color color;
  		
  		DebugLine_(soccer::Vector2 p1, soccer::Vector2 p2, Upp::Color color);
  	};
  
  	Upp::Point BoardToPixel_(soccer::Vector2 point);
	soccer::Vector2 PixelToBoard_(Upp::Point point);
  	void DrawLine_(Upp::Draw& draw, soccer::Vector2 from, soccer::Vector2 to,
  				   int width, Upp::Color color);
  	void DrawCircle_(Upp::Draw& draw, soccer::Vector2 center,
  					 int radius, Upp::Color color);
  	void WhenMove_(soccer::Direction direction);
  	void WhenFullMove_();
  	void WhenGameOver_();
  
	soccer::GameState state_;
	Upp::Size size_;
	Upp::Vector<soccer::Direction> move_;
	soccer::Vector2 moveBegin_;
	soccer::Vector2 target_;
	bool freezed_;
	bool finished_;
	std::vector<DebugLine_> debugLines_;
};

#endif
