#include "game.h"
#include "main_aux.h"
#include "stdlib.h"

Solution* create_solution(int block_w, int block_h){
	Solution* new_solution;
	int* row_start_ptr;
	int ind;
	new_solution = malloc(sizeof(Solution));
	
	if(new_solution == NULL){ /* check if allocation is successful */
		return NULL;
	}
	
	new_solution->b_w = block_w;
	new_solution->b_h = block_h;
	
	new_solution->solution_a = calloc(block_w*block_w*block_h*block_h, sizeof(int)); /* allocate (b_h*b_w)x(b_h*b_w) empty cells (0) */
	if(new_solution->solution_a == NULL){ /* check if allocation is successful */
		free(new_solution); /* free memory upon failure */
		return NULL;
	}
	
	new_solution->solution = calloc(block_w*block_h, sizeof(int*)); /* allocate (b_h*b_w) row pointers */
	if(new_solution->solution == NULL){ /* check if allocation is successful */
		free(new_solution->solution);
		free(new_solution);
		return NULL;
	}
	
	/* loop over all rows and set solution[i] to solution_a + <row_size>*i */
	for(ind=0,row_start_ptr = new_solution->solution_a; ind<block_h*block_w ; ind++, row_start_ptr += block_h*block_w){
		new_solution->solution[ind] = row_start_ptr;
	}
	
	return new_solution;
}

void destroy_solution(Solution* solution){
	free(solution->solution_a); /* free arrays used by solution */
	free(solution->solution);
	free(solution); /* free solution itself */
}

SudokuGame* create_game(int block_w, int block_h){
	return NULL; /*TODO*/
}

void destroy_game(SudokuGame* game){
	/*TODO*/
}

void print_game(SudokuGame* game){
	/*TODO*/
}

int check_value(SudokuGame* game, int x, int y, int z){
	return 0; /*TODO*/
}

int game_is_full(SudokuGame* game){
	return 0; /*TODO*/
}

Solution* generate_solution_from_board(SudokuGame* game){
	return NULL; /*TODO*/
}
