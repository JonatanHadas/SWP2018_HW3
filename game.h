#ifndef GAME_H_
#define GAME_H_
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define MAX(x, y) (((x) > (y)) ? (x) : (y))

/*
 * Game Summary:
 *
 * A container for the Sudoku game, a board the with cells of user specified size joined together into a square of user specified size
 * the game allows numbers from 1 to the size of a cell. with only one occurrence of each number in each cell, row or column.
 * The supports the next commands and functions:
 *
 * create_sudoku_board - creates a new Sudoku game board
 * set_sudoku_zero - sets all values in a game board to zero
 * copy - copies one board to another
 * destroy_sudoku - Frees all memory resources assosiated with the game
 * set - executes user command set. places user value in desired location when possible
 * hint - provides a hint for user specified location in game
 * validate - checks is the board is solvable by generating and saving a solution
 * validate_value - checks whether specified value is legal in specified position by Sodoku logic
 */


/*
 * Struct used to represent a Sudoku game board
 */
typedef struct sudoku_board{
	int size;
	int cell_size;
	int* memory;
	int** table;
}Board;

/*
 * Creates a sudoku_board struct, and returns it.
 * If function fails due to memory allocation failure returns NULL.
 */
Board* create_sudoku_board(int game_size, int game_cell_size);

/*
 * param an initialized Sudoku game
 * function changes all values to zero.
 */
void set_sudoku_zero(Board* game);

/*
 * copies the values of game into copy. Assumes they are of the same size
 */
void copy(Board* game, Board* copy);

/*
 * if param !NULL then free all allocated memory and destroy the object
 */
void destroy_sudoku(Board* game);

/*
 * prints the Sudoku board
 * "-" and "|" break the board into cells.
 * Numbers with a dot (.) near them indicate fixed numbers.
 */
void print_sudoku(Board* game);

/*
 * params: Sudoku game, x-column number
 * 1<x<(game->cell_size)*(game->cell_size),
 * y-column number 1<x<(game->cell_size)*(game->cell_size),
 * value z, 0<z<(game->cell_size)*(game->cell_size)
 * function puts z to cell (y,x) if the cell is not set.
 * checks if z is a valid possibility for loc (y,x), ie. no repeat on the same row, column or cell.
 * if is valid, puts z to cell (y,x)
 * ret=3 cell had a non zero value and was set to zero
 * ret=2 if successfully inserted z to (y,x) and number of blank spaces did not change
 * ret=1 if successfully inserted z to (y,x) previous value was zero
 * ret=0 otherwise
 */
int set(Board* game, int x, int y, int z);

/*
 * params: a board and location (x,y) where x is number of column and y number of row
 * assumes 1<=x,y,<=(game->cell_size)*(game->cell_size)
 * returns a suggested value: the value at that location in the saved solution
 */
int hint(Board* game, int x, int y);

/*
 * params: game board and a solution board. Assumes that of the same size
 * ret=0 if on the the boards is not initialized
 * ret=1 otherwise
 *
 * function takes the board that has been created with user input and attempts to solve it
 * prints if the board is solvable
 */
int validate(Board* game, Board* solution);

/*
 * params: Sudoku game, location marked by (i,j) pair. and value
 * returns if it's legal to enter value into the location (i,j).
 * ie. no occurrences of value in the same row, column or cell.
 * 0<i,j<game->size
 * 1<value<MAX_VALUE
 * ret=0 if value is not legal.
 * ret=1 if value is legal.
 */
int validate_value(Board* game,int value,int i,int j);

#endif /* GAME_H_ */
