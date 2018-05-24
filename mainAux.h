

#ifndef MAINAUX_H_
#define MAINAUX_H_

#include <time.h>
#include "game.h"

int generate_puzzle(Board *game_board, Board *solution_board,int fixed_cells);

int gameloop(Board *game_board, Board *solution_board, int fixed_cells);

#endif /* MAINAUX_H_ */
