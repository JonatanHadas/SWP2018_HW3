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
	
	/* loop over all columns and set solution[i] to solution_a + <row_size>*i */
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

Solution* copy_solution(Solution* solution){
	int i, size;
	Solution* new_solution = create_solution(solution->b_w, solution->b_h); /* allocate solution of same size */
	size = solution->b_h * solution->b_w; /* height and width of board */
	for(i = 0; i<size*size; i++){
		new_solution->solution_a[i] = solution->solution_a[i];/* copy cell */
	}
	return new_solution;
}

SudokuGame* create_game(int block_w, int block_h){
	SudokuGame* game = malloc(sizeof(SudokuGame)); /* allocate memory */
	int* row_start_ptr;
	int ind;
	
	if(game == NULL){
		return NULL;
	}
	
	game->b_w = block_w; /* set game size */
	game->b_h = block_h;
	game->sol = NULL;
	
	game->board = create_solution(block_w, block_h);
	if(game->board == NULL){
		free(game); /* on failure free all resources */
		return NULL;
	}
	
	game->fixed_a = calloc(block_w*block_w*block_h*block_h, sizeof(int)); /* allocate (b_h*b_w)x(b_h*b_w) non fixed cells (0) */
	if(game->fixed_a == NULL){
		free(game->board);
		free(game);
		return NULL;
	}
	
	game->fixed = calloc(block_w*block_h, sizeof(int*)); /* allocate (b_h*b_w) row pointers */
	if(game->fixed == NULL){
		free(game->fixed_a);
		free(game->board);
		free(game);
		return NULL;
	}
		
	/* loop over all columns and set fixed[i] to fixed_a + <row_size>*i */
	for(ind=0,row_start_ptr = game->fixed_a; ind<block_h*block_w ; ind++, row_start_ptr += block_h*block_w){
		game->fixed[ind] = row_start_ptr;
	}
	
	return game;
}

void destroy_game(SudokuGame* game){
	free(game->fixed_a);
	free(game->fixed);
	destroy_solution(game->board);
	replace_solution(game, NULL); /* clears solution if any */
	free(game);
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
					is_fixed_char = (game->fixed[col][row])? FIXED_CHAR : NON_FIXED_CHAR;
					if(game->board->solution[col][row] == 0){
						printf("%c  ", is_fixed_char); /* if 0 is saved cell is empty */
					}
					else{
						printf("%c%d ", is_fixed_char, game->board->solution[col][row]); /* print number in cell */
					}
				}
			}
			printf("|\n"); /* print last vertical line and break line */
		}
	}
}

int check_value(SudokuGame* game, int x, int y, int z){
	int size = game->b_w*game->b_h; /* board width and height */
	int row, col;
	int inr_row, inr_col; /* column and row within block */
	int blk_row, blk_col; /* row and column of block */
	int blk_start_row, blk_start_col; /* row and column of block */
	
	/* check column */
	col = x;
	for(row = 0; row<size; row++){
		if(row == y) continue; /* ignore checked cell (x,y)*/
		if(game->board->solution[col][row] == z) return FALSE;  /* found identical cell in column */
	}

	/* check row */
	row = y;
	for(col = 0; col<size; col++){
		if(col == x) continue; /* ignore checked cell (x,y)*/
		if(game->board->solution[col][row] == z) return FALSE;  /* found identical cell in column */
	}
	
	blk_row = y / game->b_h;
	blk_col = x / game->b_w;
	blk_start_row = blk_row * game->b_h;
	blk_start_col = blk_col * game->b_w;
	/* check block */
	for(inr_row = 0, row = blk_start_row; inr_row < game->b_h; inr_row++, row++){
		for(inr_col = 0, col = blk_start_col; inr_col < game->b_w; inr_col++, col++){
			if(row == y && col == x) continue; /* ignore checked cell (x,y)*/
			if(game->board->solution[col][row] == z) return FALSE;  /* found identical cell in column */
		}
	}
	
	
	return TRUE; /* no problems found */
}

int game_is_full(SudokuGame* game){
	int row, col;
	for(int row = 0; row < game->b_w * game->b_h; row++){
		for(int col = 0; col < game->b_w * game->b_h; col++){
			if(game->board->solution[col][row] == 0) return FALSE; /* empty cell detected */
		}
	}
	return TRUE; /* no empty cells detected */
}

void replace_solution(SudokuGame* game, Solution* solution){
	if(game->sol) destroy_solution(game->sol); /* if not null then destroy old solution */
	game->sol = solution;
}