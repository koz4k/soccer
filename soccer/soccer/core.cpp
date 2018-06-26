#include "core.h"

namespace soccer {

Direction reverseDirection(Direction direction)
{
	return (direction + DIR_END / 2) % DIR_END;
}

Player otherPlayer(Player player)
{
	switch(player)
	{
	  case PLAYER_1:
	  	return PLAYER_2;
	  	
	  case PLAYER_2:
	  	return PLAYER_1;
	  	
	  default:
	  	return NO_PLAYER;
	}
}
	
}
