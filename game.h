#ifndef _GAME_H
#define _GAME_H
/*
This module defines a container for sudoku games of arbitrary size,
a game includes a board, and a solution
*/

/*
This structure stores a solution for a sudoku board

contains:
int b_w  : width of block
int b_h  : height of block
note: (see same parameter in SudokuGame)

int* solution_a  : stores solution for game, contains digits from 0 to 9, row by row.
int** solution   : stores array of pointers to row beginings

note: an unfinished solution might contain 0's representing cells with yet unknown solution
*/
typedef struct sudoku_solution_t{
	int b_w,b_h;
	int * solution_a;
	int ** solution;
} Solution;

/*
Allocates empty (all 0) solution board with given block size

returns NULL on failure
*/
Solution* create_solution(int block_w, int block_h);
/*
Frees memory of given solution structure
*/
void destroy_solution(Solution* solution);

/*
creates a copy of a solution in the memory
*/
Solution* copy_solution(Solution* solution);

 /*
This structure contains a sudoku board of arbitrary size, and a solution

contains:
int b_w  : width of block
int b_h  : height of block
note: board is b_w blocks high and b_h block wide (all in all b_w*b_h cells wide and high)

Solution* board  : a partial solution representing current board situation
note: board will contain digits from 0 to 9, 0 represents an empty cell

int* fixed_a  : array of booleans 1-for fixed cell, 0-for changable.
int** fixed   : array of pointers to row beginings in fixed_a, simulates 2d array on fixed_a

Solution* sol  : solution for board
*/
typedef struct sudoku_game_t{
	int b_w,b_h;
	Solution* board;
	int* fixed_a;
	int** fixed;
	Solution* sol;
	
} SudokuGame;

/*
Allocates empty (all 0) game board with given block size

solution to game will be set to NULL pointer

returns NULL on failure
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