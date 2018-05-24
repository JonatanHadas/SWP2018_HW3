#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "game.h"
#include "solver.h"
#include "mainAux.h"

#define MAX_LENGTH 1024
#define CELL_SIZE 3
#define SIZE 9

int main(int argc, char *argv[]) {
	unsigned int seed;
	Board *game_board, *solution_board;
	int fixed_cells=0, check;
	if(argc<2) return 0;
	seed=atoi(argv[1]);
	srand(seed);
	game_board=create_sudoku_board(SIZE, CELL_SIZE);
	solution_board=create_sudoku_board(SIZE, CELL_SIZE);
	if(game_board!=NULL || solution_board!=NULL){
		while(1){
			fixed_cells=read_num_fixed_cells(SIZE*SIZE);
			if(fixed_cells==-1) break;
			check=generate_puzzle(game_board, solution_board, fixed_cells);
			if(check==-1) break;
			check=gameloop(game_board, solution_board, fixed_cells);
			if(check==4) continue; /* restart */
			if(check==5) break; /* exit */
		}
	}
	printf("Exiting...\n");
	fflush(stdout);
	destroy_sudoku(game_board);
	destroy_sudoku(solution_board);
	return 0;
}
