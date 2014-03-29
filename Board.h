#ifndef _Soccer_Board_h_
#define _Soccer_Board_h_

#include <CtrlLib/CtrlLib.h>
#include "soccer/GameState.h"

class Board: public Upp::Ctrl
{	
  public:
	Board();
	void SetBoardSize(Upp::Size size);
	virtual void Paint(Upp::Draw& w);
	virtual void MouseMove(Upp::Point point, Upp::dword);
	virtual void LeftDown(Upp::Point, Upp::dword);
	
  private:
  	Upp::Point BoardToPixel_(Upp::Point point);
	Upp::Point PixelToBoard_(Upp::Point point);
  	void DrawLine_(Upp::Draw& draw, Upp::Point from, Upp::Point to,
  				   int width, Upp::Color color);
  	void DrawCircle_(Upp::Draw& draw, Upp::Point center,
  					 int radius, Upp::Color color);
  
	soccer::GameState state_;
	Upp::Size size_;
	Upp::Vector<soccer::Direction> move_;
	Upp::Point moveBegin_;
	Upp::Point target_;
};

#endif
