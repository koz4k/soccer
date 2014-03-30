#include "Game.h"
#include "soccer/ai/Random.h"

GUI_APP_MAIN
{
	soccer::ai::Random ai;
	Game(&ai).Run();
}
