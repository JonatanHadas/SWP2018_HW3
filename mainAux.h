#ifndef MAINAUX_H_
#define MAINAUX_H_

#include <time.h>
#include "game.h"

/**
 * mainAux Summary:
 *
 * The module assists main in running the game. initializes the game and then runs all commands except restart and exit which return to the main.
 * Is a commander modul, using Parser to get input from user and interpret it, game module to execute the commands, and solver when needed.
 *
 * generate_puzzle - creates and puzzle and initializes it creating a random solution, board with fixed cells requested from user.
 * gameloop - A loop that runs through the game. processes set, hint and validate commands from the user
 */

/*
 * parameters: Two boards and a number of cells to fix 0<=fixed_cells<=80
 * ret=-1 if the fucntion failed
 * ret=1 on success
 *
 * function creates a solution and enters it into solution_board. Then chooses randomly fixed_cells number
 * of different cells and copies their value into the game board. then sets them.
 */
int generate_puzzle(Board *game_board, Board *solution_board,int fixed_cells);

/*
 * param board - is used to represent the state of the current game.
 * recieved with 0-game_board->size^2 -1 number of fixed cells that cannot be altered during the game
 * param solution_board - initialized with every cell containing a valid value.
 * param fixed_cells - the number of fixed cells in the game_board
 *
 *
 * the function runs the game receives commands from user:
 * 1. set command - in format "set X Y Z" setting location row=Y column=X with value Z if valid and not fixed.
 * 2. hint command - in format "hint X Y" returns a value, if the previous command was validate, or it's the first command
 * then the value given is valid.
 * 3. validate command - solves the board, if possible. prints whether the board is solvable. saves solution in solution_board
 * 4. restart command - returns 4
 * 5. exit command - returns 5.
 *
 * When the board is solved will print an alert to the user. only further options are exit or restart
 */
int gameloop(Board *game_board, Board *solution_board, int fixed_cells);

#endif /* MAINAUX_H_ */
