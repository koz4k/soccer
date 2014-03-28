#ifndef _Soccer_Board_h_
#define _Soccer_Board_h_

#include <CtrlLib/CtrlLib.h>

class Board: public Upp::Ctrl
{
	Upp::Size size_;
	
public:
	Board();
	void SetBoardSize(Upp::Size size);
	virtual void Paint(Upp::Draw& w);
	virtual void LeftDown(Upp::Point, Upp::dword);
};

#endif
