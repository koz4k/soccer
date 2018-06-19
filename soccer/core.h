#ifndef _soccer_core_h_
#define _soccer_core_h_

#include <functional>

namespace soccer {

typedef unsigned int u32;
typedef unsigned char u8;

const int DEFAULT_WIDTH = 8;
const int DEFAULT_HEIGHT = 10;

typedef int Direction;

// kierunki:
const Direction DIR_RIGHT = 0;
const Direction DIR_UP_RIGHT = 1;
const Direction DIR_UP = 2;
const Direction DIR_UP_LEFT = 3;
const Direction DIR_LEFT = 4;
const Direction DIR_DOWN_LEFT = 5;
const Direction DIR_DOWN = 6;
const Direction DIR_DOWN_RIGHT = 7;

// do iterowania po kierunkach:
const Direction DIR_BEGIN = 0;
const Direction DIR_END = 8;

// hubba bubba?
const Direction DIR_HUBBA_BUBBA = 9;

enum Player
{
	NO_PLAYER,
	PLAYER_1,
	PLAYER_2
};

class GameState;

typedef std::function<double(const GameState& state)> Heuristic;

Direction reverseDirection(Direction direction);
Player otherPlayer(Player player);

}

#include "Vector2.h"

#endif
#ifndef _soccer_core_h_
#define _soccer_core_h_

#include <functional>

namespace soccer {

typedef unsigned int u32;
typedef unsigned char u8;

const int DEFAULT_WIDTH = 8;
const int DEFAULT_HEIGHT = 10;

typedef int Direction;

// kierunki:
const Direction DIR_RIGHT = 0;
const Direction DIR_UP_RIGHT = 1;
const Direction DIR_UP = 2;
const Direction DIR_UP_LEFT = 3;
const Direction DIR_LEFT = 4;
const Direction DIR_DOWN_LEFT = 5;
const Direction DIR_DOWN = 6;
const Direction DIR_DOWN_RIGHT = 7;

// do iterowania po kierunkach:
const Direction DIR_BEGIN = 0;
const Direction DIR_END = 8;

// hubba bubba?
const Direction DIR_HUBBA_BUBBA = 9;

enum Player
{
	NO_PLAYER,
	PLAYER_1,
	PLAYER_2
};

class GameState;

typedef std::function<double(const GameState& state)> Heuristic;

Direction reverseDirection(Direction direction);
Player otherPlayer(Player player);

}

#include "Vector2.h"

#endif
#ifndef _soccer_core_h_
#define _soccer_core_h_

#include <functional>

namespace soccer {

typedef unsigned int u32;
typedef unsigned char u8;

const int DEFAULT_WIDTH = 8;
const int DEFAULT_HEIGHT = 10;

typedef int Direction;

// kierunki:
const Direction DIR_RIGHT = 0;
const Direction DIR_UP_RIGHT = 1;
const Direction DIR_UP = 2;
const Direction DIR_UP_LEFT = 3;
const Direction DIR_LEFT = 4;
const Direction DIR_DOWN_LEFT = 5;
const Direction DIR_DOWN = 6;
const Direction DIR_DOWN_RIGHT = 7;

// do iterowania po kierunkach:
const Direction DIR_BEGIN = 0;
const Direction DIR_END = 8;

// hubba bubba?
const Direction DIR_HUBBA_BUBBA = 9;

enum Player
{
	NO_PLAYER,
	PLAYER_1,
	PLAYER_2
};

class GameState;

typedef std::function<double(const GameState& state)> Heuristic;

Direction reverseDirection(Direction direction);
Player otherPlayer(Player player);

}

#include "Vector2.h"

#endif
#ifndef _soccer_core_h_
#define _soccer_core_h_

#include <functional>

namespace soccer {

typedef unsigned int u32;
typedef unsigned char u8;

const int DEFAULT_WIDTH = 8;
const int DEFAULT_HEIGHT = 10;

typedef int Direction;

// kierunki:
const Direction DIR_RIGHT = 0;
const Direction DIR_UP_RIGHT = 1;
const Direction DIR_UP = 2;
const Direction DIR_UP_LEFT = 3;
const Direction DIR_LEFT = 4;
const Direction DIR_DOWN_LEFT = 5;
const Direction DIR_DOWN = 6;
const Direction DIR_DOWN_RIGHT = 7;

// do iterowania po kierunkach:
const Direction DIR_BEGIN = 0;
const Direction DIR_END = 8;

// hubba bubba?
const Direction DIR_HUBBA_BUBBA = 9;

enum Player
{
	NO_PLAYER,
	PLAYER_1,
	PLAYER_2
};

class GameState;

typedef std::function<double(const GameState& state)> Heuristic;

Direction reverseDirection(Direction direction);
Player otherPlayer(Player player);

}

#include "Vector2.h"

#endif
#ifndef _soccer_core_h_
#define _soccer_core_h_

#include <functional>

namespace soccer {

typedef unsigned int u32;
typedef unsigned char u8;

const int DEFAULT_WIDTH = 8;
const int DEFAULT_HEIGHT = 10;

typedef int Direction;

// kierunki:
const Direction DIR_RIGHT = 0;
const Direction DIR_UP_RIGHT = 1;
const Direction DIR_UP = 2;
const Direction DIR_UP_LEFT = 3;
const Direction DIR_LEFT = 4;
const Direction DIR_DOWN_LEFT = 5;
const Direction DIR_DOWN = 6;
const Direction DIR_DOWN_RIGHT = 7;

// do iterowania po kierunkach:
const Direction DIR_BEGIN = 0;
const Direction DIR_END = 8;

// hubba bubba?
const Direction DIR_HUBBA_BUBBA = 9;

enum Player
{
	NO_PLAYER,
	PLAYER_1,
	PLAYER_2
};

class GameState;

typedef std::function<double(const GameState& state)> Heuristic;

Direction reverseDirection(Direction direction);
Player otherPlayer(Player player);

}

#include "Vector2.h"

#endif
#ifndef _soccer_core_h_
#define _soccer_core_h_

#include <functional>

namespace soccer {

typedef unsigned int u32;
typedef unsigned char u8;

const int DEFAULT_WIDTH = 8;
const int DEFAULT_HEIGHT = 10;

typedef int Direction;

// kierunki:
const Direction DIR_RIGHT = 0;
const Direction DIR_UP_RIGHT = 1;
const Direction DIR_UP = 2;
const Direction DIR_UP_LEFT = 3;
const Direction DIR_LEFT = 4;
const Direction DIR_DOWN_LEFT = 5;
const Direction DIR_DOWN = 6;
const Direction DIR_DOWN_RIGHT = 7;

// do iterowania po kierunkach:
const Direction DIR_BEGIN = 0;
const Direction DIR_END = 8;

// hubba bubba?
const Direction DIR_HUBBA_BUBBA = 9;

enum Player
{
	NO_PLAYER,
	PLAYER_1,
	PLAYER_2
};

class GameState;

typedef std::function<double(const GameState& state)> Heuristic;

Direction reverseDirection(Direction direction);
Player otherPlayer(Player player);

}

#include "Vector2.h"

#endif