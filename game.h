#ifndef _GAME_H
#define _GAME_H
/*
This module defines a container for sudoku games of arbitrary size,
a game includes a board, and a solution
*/

/*
This structure contains a sudoku board of arbitrary size, and a solution

contains:
int b_w  : width of block
int b_h  : height of block
note: board is b_w blocks high and b_h block wide (all in all b_w*b_h cells wide and high)

int* board_a : array containing all cells, row after row
int** board  : array of pointers to row beginings in board_a, simulates 2d array on board_a
note: board will contain digits from 0 to 9, 0 represents an empty cell

int* fixed_a  : array of booleans 1-for fixed cell, 0-for changable.
int** fixed   : array of pointers to row beginings in fixed_a, simulates 2d array on fixed_a

int* solution_a  : stores solution for game, contains digits from 1 to 9.
int** solution   : same as fixed is for fixed_a and board is for board_a
*/
typedef struct sudoku_game_t{
	int b_w,b_h;
	int * board_a;
	int ** board;
	int * fixed_a;
	int ** fixed;
	int * solution_a;
	int ** solution;
} SudokuGame;

/*
Allocates empty game board with given block size
*/
SudokuGame* create_game(int block_w, int block_h);
/*
Frees memory of given game structure
*/
void destroy_game(SudokuGame* game);

/*
Prints given game to stdout
*/
void print_game(SudokuGame* game);

/*
returns wether value z can be placed in position x,y int given game
(checks for value z in row column and block)
*/
int check_value(SudokuGame* game, int x, int y, int z);

/*
returns wether game board is full
*/
int game_is_full(SudokuGame* game);

#endif