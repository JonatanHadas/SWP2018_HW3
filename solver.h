
#ifndef SOLVER_H_
#define SOLVER_H_

#include "game.h"

#define MAX_VALUE (game->cell_size)*(game->cell_size)

int brute_solver(Board* game);

int rand_solver(Board* game);

void set_values(Board* game);



#endif /* SOLVER_H_ */
