#ifndef _Soccer_AiVsAi_h_
#define _Soccer_AiVsAi_h_

#include "MainWindow.h"
#include "soccer/Judge.h"

class AiVsAi
{
  public:
  	AiVsAi(const char* ai1Name, soccer::Ai& ai1,
  		   const char* ai2Name, soccer::Ai& ai2,
  		   int boardWidth = 8, int boardHeight = 10);
  	void Run();
  	
  private:
  	MainWindow window_;
  	soccer::Judge judge_;
  	const char* aiNames_[2];
};

#endif
