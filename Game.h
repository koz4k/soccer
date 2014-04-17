#ifndef _Soccer_Game_h_
#define _Soccer_Game_h_

#include "MainWindow.h"
#include "soccer/Ai.h"

class Game
{
  public:
  	typedef Game CLASSNAME;
  
  	Game(soccer::Ai* ai, int boardWidth = 8, int boardHeight = 10, bool playerDown = true);
  	void Run();
  	
  private:
  	void WhenFullMove_(soccer::GameState& state);
  	void WhenGameOver_(const soccer::GameState& state);
  
  	MainWindow window_;
  	soccer::Ai* ai_;
  	int playerGate_;
  	int aiGate_;
  	bool finished_;
};

#endif
