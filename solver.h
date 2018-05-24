#ifndef SOLVER_H_
#define SOLVER_H_

/**
 * Solver Summary:
 *
 * The module is used to solve the a Sudoku game in different ways.
 *
 * brute_solver - solves a game board with fixed and empty values, if possible. uses a sequential recursive function
 * rand_solver - solves an empty board uses randomization to determine next legal value to attempt. Uses a recursive function
 * set_values - fixes the non zero values in provided game board.
 */

#include "game.h"

#define MAX_VALUE (game->cell_size)*(game->cell_size)

/*
 * ret: 1, such that for every location (i,j) the value is legal. When 1<value<MAX_VALUE, if possible.
 * ret: 0, when no legal solution is possible with current set values.
 *
 * utilizes recursive function "brute_solver_rec(Board* game, int i, int j)":
 *
 * parameters: game is the Sudoku game, (i,j) indicate position on the Sudoku board
 * 0<i,j<game->size
 * function recursively traverses the board. leaves fixed values untouched (marked with a minus).
 * function sweeps the board from left to right and from bottom down
 * Each time the function gets to a non fixed position (i,j), it will run sequentially on numbers 1-MAX_VALUE till it finds a valid input
 * once one valid input is found will proceed to the next cell.
 * When all possible inputs are invalid in current state will backtrack to previous location.
 * At previous location will continue sequentially attempts over possible values.
 *
 * ret: 1, such that for every location (i,j) the value is legal. When 1<value<MAX_VALUE, if possible.
 * ret: 0, when no legal solution is possible with current set values. or an error has been encountered.
 */
int brute_solver(Board* game);

/*
 * ret: 1, such that for every location (i,j) the value is legal. When 1<value<MAX_VALUE, if possible.
 * ret: 0, when no legal solution is possible with current set values.
 * Allocates an validity table for each cell in the game board with the size of MAX_VALUE
 * passes on the tables to the recursive function:
 *
 * utilizes recursive function "rand_solver_rec(Board* game, int** avilability_table, int i, int j)":
 *
 * parameters: game is the Sudoku game, and availability table.
 * (i,j) indicate position on the Sudoku board 0<i,j<game->size
 * function recursively traverses the board. function sweeps the board from left to right and from bottom down
 * Such that each cell prior to current one are full with valid numbers
 * Each step to an untouched, all valid possibilities for the cell are calculated
 * it will randomly choose a value from among valid values with function "get_random_num". Or deterministically the value if only one available
 * Then proceed to the next cell.
 * When all possible inputs are invalid in current state will backtrack to previous location. the validity tables are cleaned.
 * Where a new valid value will be chosen randomly. sans previously used ones
 *
 * ret: 1, such that for every location (i,j) the value is legal. When 1<value<MAX_VALUE, if possible.
 * ret: 0, when no legal solution is possible with current set values.
 */
int rand_solver(Board* game);

/*
 * negative integers on the board indicate values that are set, and cannot be changed.
 * Fucntion sets all non zero values.
 */
void set_values(Board* game);

#endif /* SOLVER_H_ */
