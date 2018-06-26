#include "AiStandalone.h"
#include <ctime>
#include <cstdio>

namespace soccer {

AiStandalone::AiStandalone(Ai* ai):
	ai_(ai), endTime_(0), initialized_(false)
{
}

AiStandalone::~AiStandalone()
{
	delete ai_;
}

void AiStandalone::run()
{
	char command[10];
	while(scanf("%s", command) == 1)
	{
		int a = 0, b = 0;
		switch(command[0])
		{
		  case 'b':
		  	scanf("%u %u", &a, &b);
		  	boardsize_(a, b);
		  	printf("=\n");
		  	break;
		  	
		  case 't':
		  	scanf("%u", &a);
		  	timeleft_(a);
		  	printf("=\n");
		  	break;
		  	
		  case 'p':
		  	scanf("%u", &a);
		  	play_(a);
		  	printf("=\n");
		  	break;
		  	
		  case 'g':
		  	printf("= %u\n", genmove_());
		  	break;
		}
		
		fflush(stdout);
	}
}

void AiStandalone::boardsize_(int width, int height)
{
	state_ = GameState(width, height);
}

void AiStandalone::timeleft_(int ms)
{
	endTime_ = clock() * 1000 / CLOCKS_PER_SEC + ms;
}

// TODO: sanity checks
void AiStandalone::play_(int direction)
{
	if(!initialized_)
	{
		state_.setWhoseTurn(PLAYER_2);
		initialized_ = true;
	}
	
	ai_->opponentMoved((Direction) direction);
	state_.move((Direction) direction);
}

// TODO: sanity checks
int AiStandalone::genmove_()
{
	Direction direction = ai_->move(state_, getTimeLeft_());
	state_.move(direction);
	return direction;
}

int AiStandalone::getTimeLeft_() const
{
	return endTime_ - clock() * 1000 / CLOCKS_PER_SEC;
}
	
}