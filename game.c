#include "game.h"
#include "solver.h"
#include <stdio.h>
#include <stdlib.h>

void print_seperator(int size, int cell_size);

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

void set_sudoku_zero(Board* game){
	int i=0, j=0;
	for(;i<(game->size);i++){
		for(j=0;j<(game->size);j++){
			game->table[i][j]=0;
		}
	}
	return;
}

void copy(Board* game, Board* copy){
	int i=0, j=0;
	for(;i<(game->size);i++){
		for(j=0;j<(game->size);j++){
			copy->table[i][j]=game->table[i][j];
		}
	}
	return;
}

void destroy_sudoku(Board* game){
	if(!game) return;
	free(game->memory);
	free(game->table);
	free(game);
	return;
}

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

int set(Board* game, int x, int y, int z){
	int current_val;
	x--, y--; /* implementation starts locs at 0 */
	current_val=game->table[y][x];
	if(!game) return -1;
	if(game->table[y][x]<0){
		printf("Error: cell is fixed\n");
		fflush(stdout);
		return 0;
	}
	else if(z==0 || validate_value(game, z, y, x)){
		game->table[y][x]=z;
		if((z>0 && current_val>0) || (z==0 && current_val==0)) return 2; /* number of blank spaces doesn't change */
		if(z==0 && current_val>0) return 3;
		return 1;
	}
	else{
		printf("Error: value is invalid\n");
		fflush(stdout);
		return 0;
	}
	return 0;
}

int hint(Board* game, int x, int y){
	x--, y--; /* implementation starts locs at 0 */
	if(!game) return -1;
	printf("Hint: set cell to %d\n",MAX(game->table[y][x],(-1)*(game->table[y][x])));
	fflush(stdout);
	return 1;
}

int validate(Board* game, Board* solution){
	int check=0;
	Board *temp_board;
	if(!game || !solution) return -1;
	temp_board=create_sudoku_board(game->size,game->cell_size);
	copy(game,temp_board);
	check=brute_solver(temp_board);
	if(check==0){
		printf("Validation failed: board is unsolvable\n");
	}
	else {
		copy(temp_board,solution);
		printf("Validation passed: board is solvable\n");
	}
	destroy_sudoku(temp_board);
	return 1;
}

int validate_value(Board* game,int value,int i,int j){
	int k=0, s=0, t=0, cell_size=game->cell_size;
	int cell_loc[2];
	cell_loc[0]=cell_size*(i/(cell_size));
	cell_loc[1]=cell_size*(j/(cell_size));
	/* checking same row */
	for(k=0;k<(game->size);k++){
		if(k!=j && MAX(game->table[i][k],(-1)*(game->table[i][k]))==value) return 0;
	}
	/* checking same column */
	for(k=0;k<(game->size);k++){
		if(k!=i && MAX(game->table[k][j],(-1)*(game->table[k][j]))==value) return 0;
	}
	/* checking same cell */
	for(s=cell_loc[0];s<cell_size+cell_loc[0];s++){
		for(t=cell_loc[1];t<cell_size+cell_loc[1];t++){
			if(s==i && t==j) continue;
			if(MAX(game->table[s][t],(-1)*(game->table[s][t]))==value) return 0;
		}
	}
	return 1; /*value is legal*/
}
