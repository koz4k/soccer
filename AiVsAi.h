#ifndef _Soccer_AiVsAi_h_
#define _Soccer_AiVsAi_h_

#include "MainWindow.h"
#include "soccer/Judge.h"
#include <string>

class AiVsAi
{
  public:
  	AiVsAi(std::string ai1Name, soccer::Ai& ai1,
  		   std::string ai2Name, soccer::Ai& ai2,
  		   int boardWidth = 8, int boardHeight = 10);
  	void Run();
  	
  private:
  	MainWindow window_;
  	soccer::Judge judge_;
  	std::string aiNames_[2];
};

#endif
