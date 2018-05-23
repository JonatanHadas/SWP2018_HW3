

#ifndef GAME_H_
#define GAME_H_
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define MAX(x, y) (((x) > (y)) ? (x) : (y))

typedef struct sudoku_board{
	int size;
	int cell_size;
	int* memory;
	int** table;
}Board;

Board* create_sudoku_board(int game_size, int game_cell_size);

void set_sudoku_zero(Board* game);

void copy(Board* game, Board* copy);

void destroy_sudoku(Board* game);

void print_sudoku(Board* game);

int set(Board* game, int x, int y, int z);

int hint(Board* game, int x, int y);

int validate(Board* game, Board* solution);

int validate_value(Board* game,int value,int i,int j);

#endif /* GAME_H_ */
