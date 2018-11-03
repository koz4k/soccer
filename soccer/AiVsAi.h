#ifndef _soccer_AiVsAi_h_
#define _soccer_AiVsAi_h_

#include "MainWindow.h"
#include "soccer/Judge.h"
#include <memory>
#include <string>

class AiVsAi
{
  public:
  	AiVsAi(std::string ai1Name, std::unique_ptr<soccer::Ai> ai1,
  		   std::string ai2Name, std::unique_ptr<soccer::Ai> ai2,
  		   int boardWidth = 8, int boardHeight = 10);
  	void Run();
  	
  private:
  	MainWindow window_;
  	soccer::Judge judge_;
  	std::string aiNames_[2];
    std::unique_ptr<soccer::Ai> ais_[2];
};

#endif
