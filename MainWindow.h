#ifndef _soccer_MainWindow_h
#define _soccer_MainWindow_h

#include <CtrlLib/CtrlLib.h>
#include "Board.h"

using namespace Upp;

#define LAYOUTFILE <soccer/Main.lay>
#include <CtrlCore/lay.h>

class MainWindow: public WithMainLayout<Upp::TopWindow>
{
  public:
	typedef MainWindow CLASSNAME;
	
	MainWindow();
};

#endif