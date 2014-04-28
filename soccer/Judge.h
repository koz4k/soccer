#ifndef _Soccer_Judge_h_
#define _Soccer_Judge_h_

#include "Ai.h"

namespace soccer {

class Judge
{
  public:
  	Judge(Ai* player1, Ai* player2, int boardWidth = 8, int boardHeight = 10);
  	Judge(Ai* player1, Ai* player2, GameState state);
  	const GameState& getGameState() const;
  	const GameState& oneMove();
  	GameState run();
  
  private:
  	// nie zwalnia Ai-ow
  	Ai* player1_;
  	Ai* player2_;
  	GameState state_;
};
	
}

#endif
