#ifndef _Soccer_MainWindow_h
#define _Soccer_MainWindow_h

#include <CtrlLib/CtrlLib.h>
#include "Board.h"

using namespace Upp;

#define LAYOUTFILE <Soccer/Main.lay>
#include <CtrlCore/lay.h>

class MainWindow: public WithMainLayout<Upp::TopWindow>
{
  public:
	typedef MainWindow CLASSNAME;
	
	MainWindow();
};

#endif