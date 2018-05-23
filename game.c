

#include "game.h"
#include "solver.h"
#include <stdio.h>
#include <stdlib.h>

void print_seperator(int size, int cell_size);

/*
 * Creates a sudoku_board struct, and returns it.
 * If function fails due to memory allocation failure returns NULL.
 */
Board* create_sudoku_board(int game_size, int game_cell_size){
	Board* game_board;
	int i=0;

	game_board=(Board*) malloc(sizeof(Board));
	if(!game_board){ /* allocation failed */
		printf("Error: malloc has failed\n");
		return NULL;
	}
	game_board->memory=calloc(game_size*game_size,sizeof(int));
	game_board->table=calloc(game_size,sizeof(int*));
	if(!game_board->table || !game_board->memory){ /* allocation failed */
		printf("Error: calloc has failed\n");
		return NULL;
	}
	game_board->size=game_size;
	game_board->cell_size=game_cell_size;
	for(i=0;i<game_size;i++){
		game_board->table[i] = game_board->memory+i*game_size;
	}
	return game_board;
}

/*param an initialized Sudoku game
 * function changes all values to zero.
 */
void set_sudoku_zero(Board* game){
	int i=0, j=0;
	for(;i<(game->size);i++){
		for(j=0;j<(game->size);j++){
			game->table[i][j]=0;
		}
	}
	return;
}

/*
 * copies the values of game into copy. Assumes they are of the same size
 */
void copy(Board* game, Board* copy){
	int i=0, j=0;
	for(;i<(game->size);i++){
		for(j=0;j<(game->size);j++){
			copy->table[i][j]=game->table[i][j];
		}
	}
	return;
}

/*
 * if param !NULL then free all allocated memory and destroy the object
 */
void destroy_sudoku(Board* game){
	if(!game) return;
	free(game->table);
	free(game->memory);
	free(game);
	return;
}

/*
 * prints the Sudoku board
 * "-" and "|" break the board into cells.
 * Numbers with a dot (.) near them indicate fixed numbers.
 */
void print_sudoku(Board* game){
	int i=0, j=0;
	for(;i<(game->size);i++){
		if(i%(game->cell_size)==0){
			print_seperator(game->size,game->cell_size);
		}
		for(j=0;j<(game->size);j++){
			if(j%(game->cell_size)==0){
				printf("| ");
			}
			if(game->table[i][j]==0){ /* empty location */
				printf("   ");
			}
			else if(game->table[i][j]>0){ /* non fixed value */
				printf(" %d ",game->table[i][j]);
			}
			else{ /* fixed value */
				printf(".%d ",(-1)*(game->table[i][j]));
			}
		}
		printf("|\n");
	}
	print_seperator(game->size,game->cell_size);
}

/*
 * prints (length) number of "-" chars.
 * assumes length >=0
 */
void print_seperator(int size, int cell_size){
	/*each value takes three spaces, each wall takes two except for the last one.
	 * number of walls is (size/cell_size) without counting the last one. and +1 for last wall.*/
	int i=(size*3)+2*(size/cell_size)+1;
	for(;i>0;i--) printf("-");
	printf("\n");
}

/* commands */

/*
 * params: Sudoku game, x-column number
 * 1<x<(game->cell_size)*(game->cell_size),
 * y-column number 1<x<(game->cell_size)*(game->cell_size),
 * value z, 0<z<(game->cell_size)*(game->cell_size)
 * function puts z to cell (y,x) if the cell is not set.
 * checks if z is a valid possibility for loc (y,x), ie. no repeat on the same row, column or cell.
 * if is valid, puts z to cell (y,x)
 * ret=1 if successfully inserted z to (y,x)
 * ret=0 otherwise
 */
int set(Board* game, int x, int y, int z){
	x--, y--; /* implementation starts locs at 0 */
	if(!game) return -1;
	if(game->table[y][x]<0){
		printf("Error: cell is fixed\n");
		fflush(stdout);
		return 0;
	}
	else if(z==0 || validate_value(game, z, y, x)){
		game->table[y][x]=z;
		return 1;
	}
	else{
		printf("Error: value is invalid\n");
		fflush(stdout);
		return 0;
	}
	return 0;
}

/*
 * params: a board and location (x,y) where x is number of column and y number of row
 * assumes 1<=x,y,<=(game->cell_size)*(game->cell_size)
 * returns a suggested value: the value at that location in the saved solution
 */
int hint(Board* game, int x, int y){
	x--, y--; /* implementation starts locs at 0 */
	if(!game) return -1;
	printf("Hint: set cell to %d\n",MAX(game->table[y][x],(-1)*(game->table[y][x])));
	fflush(stdout);
	return 1;
}

/*
 * params: game board and a solution board. Assumes that of the same size
 * ret=0 if on the the boards is not initialized
 * ret=1 otherwise
 *
 * function takes the board that has been created with user input and attempts to solve it
 * prints if the board is solvable
 */
int validate(Board* game, Board* solution){
	int check=0;
	if(!game || !solution) return -1;
	copy(game,solution);
	check=brute_solver(solution);
	if(check==0){
		printf("Validation failed: board is unsolvable\n");
	}
	else printf("Validation passed: board is solvable\n");
	fflush(stdout);
	return 1;
}

/*
 * params: Sudoku game, location marked by (i,j) pair. and value
 * returns if it's legal to enter value into the location (i,j).
 * ie. no occurrences of value in the same row, column or cell.
 * 0<i,j<game->size
 * 1<value<MAX_VALUE
 * ret=0 if value is not legal.
 * ret=1 if value is legal.
 */
int validate_value(Board* game,int value,int i,int j){
	int k=0, s=0, t=0, cell_size=game->cell_size;
	int cell_loc[2];
	cell_loc[0]=cell_size*(i/(cell_size));
	cell_loc[1]=cell_size*(j/(cell_size));
	/* checking same row */
	for(k=0;k<(game->size);k++){
		if(MAX(game->table[i][k],(-1)*(game->table[i][k]))==value) return 0;
	}
	/* checking same column */
	for(k=0;k<(game->size);k++){
		if(MAX(game->table[k][j],(-1)*(game->table[k][j]))==value) return 0;
	}
	/* checking same cell */
	for(s=cell_loc[0];s<cell_size+cell_loc[0];s++){
		for(t=cell_loc[1];t<cell_size+cell_loc[1];t++){
			fflush(stdout);
			if(MAX(game->table[s][t],(-1)*(game->table[s][t]))==value) return 0;
		}
	}
	return 1; /*value is legal*/
}

