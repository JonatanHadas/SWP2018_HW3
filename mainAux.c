

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "mainAux.h"
#include "solver.h"
#include "game.h"
#include "parser.h"

/*
 * parameters: Two boards and a number of cells to fix 0<=fixed_cells<=80
 * ret=-1 if the fucntion failed
 * ret=1 on success
 *
 * function creates a solution and enters it into solution_board. Then chooses randomly fixed_cells number
 * of different cells and copies their value into the game board. then sets them.
 */
int generate_puzzle(Board *game_board, Board *solution_board,int fixed_cells){
	int check=0, set_cells=0;
	int random_loc[2];

	set_sudoku_zero(solution_board);
	set_sudoku_zero(game_board);

	check=rand_solver(solution_board);
	if (check==0) return -1; /* error solving board */
	while(set_cells<fixed_cells){
		random_loc[0]=rand()%(game_board->size);  /* randomly choosing a cell */
		random_loc[1]=rand()%(game_board->size);
		if(game_board->table[random_loc[1]][random_loc[0]]==0){ /* only copy the content if it wasn't set before */
			game_board->table[random_loc[1]][random_loc[0]]=solution_board->table[random_loc[1]][random_loc[0]];
			set_cells++;
		}
	}
	set_values(game_board);
	return 1;
}

int gameloop(Board *game_board, Board *solution_board, int fixed_cells){
	int num_unsolved, check=0, finished=0;
	int user_input[4]={0,0,0,0};
	num_unsolved=(game_board->size)*(game_board->size)-fixed_cells;
	while(1){
		print_sudoku(game_board);
		fflush(stdout);
		get_command(user_input, finished);
		switch(user_input[0]){
			case 1:{
				check=set(game_board, user_input[1], user_input[2], user_input[3]);
				if(check==1){ /* successfully set */
					num_unsolved--;
				}
				break;
			}
			case 2: {
				check=hint(solution_board, user_input[1], user_input[2]);
				break;
			}
			case 3:{
				check=validate(game_board, solution_board);
				break;
			}
			case 4:{
				return 4; /* restart */
			}
			case 5:{
				return 5; /* exit */
			}
		}
		if(check==-1) return 5; /* there was an error with board, exit */
		if(num_unsolved<0)finished=1; /* game is solved successfully */
	}
	return 0;
}
