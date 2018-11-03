# Paper soccer bot

This repo contains code for the winning submission to the [Artificial Intelligence in Games Contest](http://games.mimuw.edu.pl/pilka/) (page in Polish) organized in 2014 at the Faculty of Mathematics, Informatics and Mechanics at the University of Warsaw. Since then it has laid lost and forgotten on my computer until I finished my studies in 2018. Then I decided that the code might still be useful to someone, so I cleaned it up and put it on GitHub.

## Getting started

This project uses the CMake build system. To build, run:

```bash
mkdir build && cd build && cmake .. && make
```

The binary will appear in `build/bin/soccer`. By default, it will launch a GUI for playing with the best version of the bot. It's quite hard to beat, at least for me :wink:

The GUI uses the [Ultimate++ framework](https://www.ultimatepp.org/). The relevant part of it is included in this repo.

## Game

![Screenshot of the board](/screenshot.png)

Paper soccer is played by two people on a quadratic grid in shape of a rectangle. There are two goals, one for each player, placed on the opposite sides of the grid. At the beginning of the game, the ball is placed at the center of the grid, at an intersection of lines. Players make their turns moving the ball to an adjacent intersection in one of the 8 directions by drawing a line between the old and new position. Lines cannot be drawn over existing lines. If a player reaches a point already connected with a line (or an edge of the grid), the ball "bounces" and they get another turn. The player who places the ball in the other player's goal wins.

The game is described in more detail on the [Wikipedia](https://en.wikipedia.org/wiki/Paper_soccer).

## Algorithms

For the purpose of this contest I implemented various strategies, including [alpha-beta pruning](https://en.wikipedia.org/wiki/Alpha%E2%80%93beta_pruning), [Monte Carlo tree search](https://en.wikipedia.org/wiki/Monte_Carlo_tree_search) with various improvements (including RAVE) and other, simpler heuristics.

Implementations of those algorithms can be found at `soccer/ai`. The strategies are composable, for example MCTS can use any other strategy for generating playouts.

## Modes

Coming up with the solution required a lot of experimentation, tuning the parameters by setting bots against each other and playing with them manually to understand their flaws. Much of the code for those experiments is included in this repo as switchable "modes" - `.hpp` files containing actual code, that can be switched by changing the following line in `soccer/main.cpp` before building the binary:

```c++
#define MODE play
```

List of modes:

* `play` - default mode, a GUI for playing with the best version of the bot (MCTS)
* `generator` - a tool for generating openings, not used in the final submission
* `standalone_ab`, `standalone_mcts` - standalone versions of the alpha-beta and MCTS bot respectively, communicating via stdin and stdout according to the contest protocol
* `ab_contest`, `mcts_contest`, `k_tuning`, `sanity_contest`, `time_contest`, `timing_test` - various experiments with bots playing against each other, for comparing them and tuning their parameters

## Acknowledgements

Many thanks to [Jakub Pawlewicz](https://www.mimuw.edu.pl/~pan/), who organized the contest and prepared the materials that enabled implementing this bot.
