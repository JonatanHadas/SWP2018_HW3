


#include "mainAux.h"
#include "solver.h"
#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int brute_solver_rec(Board* game, int i, int j);
int validate_value(Board* game,int value,int i,int j);
int get_random_num(int *values, int num_valid);
int rand_solver_rec(Board* game, int** avilability_table, int i, int j);

/*
 * ret: 1, such that for every location (i,j) the value is legal. When 1<value<MAX_VALUE, if possible.
 * ret: 0, when no legal solution is possible with current set values.
 */
int brute_solver(Board* game){
	set_values(game);
	return brute_solver_rec(game,0,0);
}

/*
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
 * ret: 0, when no legal solution is possible with current set values.
 */
int brute_solver_rec(Board* game, int i, int j){
	int value=1;
	if(game->table[i][j]<0){
		if((i==game->size-1)&&(j==game->size-1)) return 1; /* success! */
		return(brute_solver_rec(game,i+((j+1)/(game->size)),(j+1)%(game->size)));
	}
	else{
		for(value=1;value<=(MAX_VALUE);value++){
			if(validate_value(game, value, i, j)){
				game->table[i][j]=value;
				if((i==game->size-1)&&(j==game->size-1)) return 1; /* success! */
				if(brute_solver_rec(game,i+((j+1)/(game->size)),(j+1)%(game->size))) return 1;
			}
			else if(value==MAX_VALUE){
				game->table[i][j]=0;
			}
		}
	}
	return 0;
}

int rand_solver(Board* game){
	int i=0;
	int* mem_aloc;
	int** avilability_table;
	mem_aloc=calloc(MAX_VALUE*(game->size)*(game->size),sizeof(int));
	avilability_table=calloc((game->size)*(game->size),sizeof(int*));
	if(!avilability_table || !mem_aloc){ /* allocation failed */
		printf("Error: calloc has failed\n");
		return 0;
	}
	for(i=0;i<(game->size)*(game->size);i++){
		avilability_table[i] = mem_aloc+i*MAX_VALUE;
	}
	return rand_solver_rec(game, avilability_table, 0, 0);

}

int rand_solver_rec(Board* game, int** avilability_table, int i, int j){
	int* values;
	int k=0, num_valid=0, random_number;
	values=avilability_table[i*(game->size)+j];

	for(;k<MAX_VALUE;k++){
		if(validate_value(game, k+1, i, j)){
			values[k]=1;
			num_valid++;
		}
		else values[k]=0;
	}

/*	print_sudoku(game);
	fflush(stdout); */

	while(num_valid>0){
/*		printf("(i,j)=(%d,%d)",i+1,j+1);
		printf("num_valid: %d  values: ",num_valid);
		for(k=0;k<MAX_VALUE;k++){
			if(values[k]==1){
				printf("%d, ", k+1);}}
		printf("\n");
		fflush(stdout); */
		random_number=get_random_num(values, num_valid);
		num_valid--;
		game->table[i][j]=random_number;
		if((i==game->size-1)&&(j==game->size-1)) return 1; /* success! */
		if(rand_solver_rec(game, avilability_table, i+((j+1)/(game->size)),(j+1)%(game->size))) return 1;
	}
	game->table[i][j]=0;
	return 0;
}

/*
 * negative integers on the board indicate values that are set, and cannot be changed.
 * Fucntion sets all non zero values.
 */
void set_values(Board* game){
	int i=0, j=0;
	for(;i<(game->size);i++){
		for(j=0;j<(game->size);j++){
			game->table[i][j]=MIN(game->table[i][j], ((-1)*(game->table[i][j])));
		}
	}
}


/*
 * gets an array of possible values. a cell in the array with value 1 indicates that the index+1 of cell is valid.
 * 0 indicate invalid.
 * If there is only one valid num, the function returns it. otherwise it uses rand() to select the index of the random number from all valid ones
 * returns one of the valid values.
 */
int get_random_num(int *values,int num_valid){
	int i=0, random_index=0; /* case there is only one valid number set the "random index" to first*/
	if(num_valid>1){ /* otherwise use random to choose index */
		random_index=rand()%num_valid;
	}
	for(;random_index>=0;i++){
		if(values[i]==1) random_index--;
	}
	values[i-1]=0; /*sets 0 for the num we're about to use */
	return i;
}


