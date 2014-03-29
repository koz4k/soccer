#ifndef _Soccer_core_h_
#define _Soccer_core_h_

namespace soccer {

typedef unsigned int u32;
typedef unsigned char u8;

const int DEFAULT_WIDTH = 8;
const int DEFAULT_HEIGHT = 10;

typedef int Direction;

const Direction DIR_RIGHT = 0;
const Direction DIR_UP_RIGHT = 1;
const Direction DIR_UP = 2;
const Direction DIR_UP_LEFT = 3;
const Direction DIR_LEFT = 4;
const Direction DIR_DOWN_LEFT = 5;
const Direction DIR_DOWN = 6;
const Direction DIR_DOWN_RIGHT = 7;

const Direction DIR_BEGIN = 0;
const Direction DIR_END = 8;

Direction reverseDirection(Direction direction);

}

#include "Point.h"

#endif
