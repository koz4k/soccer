#ifndef _Soccer_PlayerVsAi_h_
#define _Soccer_PlayerVsAi_h_

#include "MainWindow.h"
#include "soccer/Ai.h"

class PlayerVsAi
{
  public:
  	typedef PlayerVsAi CLASSNAME;
  
  	PlayerVsAi(soccer::Ai* ai, int boardWidth = 8, int boardHeight = 10);
  	void Run();
  	
  private:
  	void WhenFullMove_(soccer::GameState& state);
  	void WhenGameOver_(const soccer::GameState& state);
  
  	MainWindow window_;
  	soccer::Ai* ai_;
  	bool finished_;
};

#endif
