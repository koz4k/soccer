#ifndef MAIN
#define MAIN standalone_mcts
#endif

#define QUOTEME(x) QUOTEME_1(x)
#define QUOTEME_1(x) #x
#define INCLUDE_HPP(name) QUOTEME(name.hpp)

#include INCLUDE_HPP(MAIN)