#include "game.h"
#include "main_aux.h"
#include <stdlib.h>
#include <stdio.h>

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

#define FIXED_CHAR ('.')
#define NON_FIXED_CHAR (' ')

void print_game(SudokuGame* game){
	int blk_row, blk_col; /* index of rows and columns of blocks */
	int inr_row, inr_col; /* row and column within block (inner row and column)*/
	int row, col; /* actual row and column */
	char is_fixed_char; /* character will change according to current cell */
	
	for(row = blk_row = 0; blk_row <= game->b_w; blk_row++){ /* loop over b_w rows of blocks and an extra line at the end*/
		/* print horizontal line between blocks */
		for(blk_col = 0; blk_col < game->b_h; blk_col++){
			for(inr_col = 0; inr_col < game->b_w; inr_col++){
				printf("---"); /* cell is 3 characters wide */
			}
			printf("--"); /* 2 characters more per block */
		}
		printf("-\n"); /* one last character and line break */
		
		
		if(blk_row == game->b_w) continue; /* an if we are one row beyond end, only print hotizontal line */
		
		for(inr_row = 0; inr_row < game->b_h; row++, inr_row++){ /* loop over b_h rows within a block */
			for(blk_col = col = 0; blk_col < game->b_h; blk_col++){ /* loop over b_h columns of blocks */
				printf("| "); /* print vertical line between blocks */
				for(inr_col = 0; inr_col < game->b_w; inr_col++, col++){ /* loop over b_w columns within a block */
					is_fixed_char = (game->fixed[row][col])? FIXED_CHAR : NON_FIXED_CHAR;
					if(game->board->solution[row][col] == 0){
						printf("%c  ", is_fixed_char); /* if 0 is saved cell is empty */
					}
					else{
						printf("%c%d ", is_fixed_char, game->board->solution[row][col]); /* print number in cell */
					}
				}
			}
			printf("|\n"); /* print last vertical line and break line */
		}
	}
}

int check_value(SudokuGame* game, int x, int y, int z){
	return 0; /*TODO*/
}

int game_is_full(SudokuGame* game){
	int row, col;
	for(int row = 0; row < game->b_w * game->b_h; row++){
		for(int col = 0; col < game->b_w * game->b_h; col++){
			if(game->board->solution[row][col] == 0) return FALSE; /* empty cell detected */
		}
	}
	return TRUE; /* no empty cells detected */
}

Solution* generate_solution_from_board(SudokuGame* game){
	return NULL; /*TODO*/
}
