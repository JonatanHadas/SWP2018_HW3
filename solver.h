#ifndef _SOLVER_H
#define _SOLVER_H

#include "game.h"

/*
This module provides functions for solving and generating game boards
*/

/*
Generates a solution to a given board deterministicaly, and returns it

if there is no solution returns NULL
*/
Solution* solve_det(SudokuGame* game);

/*
Generates a randomized solution to a given board, and returns it

if there is no solution returns NULL
*/
Solution* solve_rand(SudokuGame* game);

/*
Generates a new game with a given number of fixed cells, and a saved solution
*/
SudokuGame* generate_game(int num_fixed);

#endif