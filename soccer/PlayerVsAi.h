#ifndef _soccer_PlayerVsAi_h_
#define _soccer_PlayerVsAi_h_

#include "MainWindow.h"
#include "soccer/Ai.h"
#include <memory>

class PlayerVsAi
{
  public:
  	typedef PlayerVsAi CLASSNAME;
  
    PlayerVsAi(std::unique_ptr<soccer::Ai> ai, int boardWidth = 8, int boardHeight = 10);
  	void Run();
  	
  private:
  	void WhenMove_(const soccer::GameState& state, soccer::Direction direction);
  	void WhenFullMove_(soccer::GameState& state);
  	void WhenGameOver_(const soccer::GameState& state);
  
  	MainWindow window_;
    std::unique_ptr<soccer::Ai> ai_;
  	bool finished_;
};

#endif
