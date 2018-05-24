

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_COMMAND_LENGTH 1024
#define SET_COMMAND 1
#define HINT_COMMAND 2
#define VALIDATE_COMMAND 3
#define RESTART_COMMAND 4
#define EXIT_COMMAND 5

int get_number_from_string(char *input_string);
int isDigit(char c);

/*
 * param max number of fixed cells.
 * 0<=ret<max_cells when successful
 * ret =-1 if the function failed
 *
 * function read the input from the user if it's a valid number, returns it. If invalid number asks the user again.
 * If it's another input exits with an eror
 */
int read_num_fixed_cells(int max_cells){
	int fixed_cells=0, check=0;
	while(1){
		printf("Please enter the number of cells to fill [0-%d]:\n",max_cells-1);
		fflush(stdout);
		check=scanf("%d",&fixed_cells);
		if(check<0){ /* string contains EOF, command is exit */
			fixed_cells=-1;
			break;
		}
		if(fixed_cells>=0 && fixed_cells<max_cells) break;
		printf("Error: invalid number of cells to fill (should be between 0 and %d)\n",max_cells-1);
		fflush(stdout);
	}
	return fixed_cells;
}


/*
 * Assuming that result =/= NULL and contains space for 4 integers
 * ret[0] describes the command from user.
 * 1.set  2.hint  3.validate  4.restart  5.exit
 * in case of EOF uses exit command
 * when finished !=0 only commands 4.restart 5.exit are accepted
 * ret[1]-ret[3] are used for command parameters when needed
 */
int* get_command(int *result, int finished){
	int num_from_string=-1, i=0;
	char *input_string = malloc(MAX_COMMAND_LENGTH), *check = NULL, *token = NULL, *delimiter=" \t\r\n";
	if(input_string==NULL){
		printf("Error: malloc has failed\n");
		fflush(stdout);
		*result=EXIT_COMMAND;
		return result;
	}

	while(1){
		check = fgets(input_string,MAX_COMMAND_LENGTH,stdin);
		if(check==NULL){ /* string contains EOF, command is exit */
			*result=EXIT_COMMAND;
			free(input_string);
			return result;
		}
		token=strtok(input_string,delimiter);
		if (token == NULL){ /*input is only white spaces, get new input*/
			continue;
		}
		if(finished==0 && strcmp(token,"set")==0){ /* case command is set */
			*result=SET_COMMAND;
			for(i=1;i<=3;i++){  	/* get the cell and value */
				token = strtok(NULL, delimiter);
				num_from_string=get_number_from_string(token);
				if(num_from_string==-1){  /* invalid command */
					printf("Error: invalid command\n");
					fflush(stdout);
					break;
				}
				result[i]=num_from_string;
			}
			if(num_from_string==-1) continue; /* invalid command - get next one */
			break;
		}
		if(finished==0 && strcmp(token,"hint")==0){ /* case command is hint */
			*result=HINT_COMMAND;
			for(i=1;i<=2;i++){ /* get the cell */
				token = strtok(NULL, delimiter);
				num_from_string=get_number_from_string(token);
				if(num_from_string==-1){ /* invalid command */
					printf("Error: invalid command\n");
					fflush(stdout);
					break;
				}
				result[i]=num_from_string;
			}
			if(num_from_string==-1) continue; /* invalid command - get next one */
			break;
		}
		if(finished==0 && strcmp(token,"validate")==0){  /* case command is validate */
			*result=VALIDATE_COMMAND;
			break;
		}
		if(strcmp(token,"restart")==0){  /* case command is restart */
			*result=RESTART_COMMAND;
			break;
		}
		if(strcmp(token,"exit")==0){  /* case command is exit */
			*result=EXIT_COMMAND;
			break;
		}
		else{
			printf("Error: invalid command\n");
			fflush(stdout);
		}
	}
	free(input_string);
	return result;
}

/*
 * gets an input string.
 * if string is empty or contains anything but numbers, return -1: Eror
 * returns the string parsed to an int number
 */
int get_number_from_string(char *input_string){
	long unsigned size=0;
	int i=0, result=0, decimal=1;
	if(input_string==NULL) return -1;
	size= strlen(input_string);
	if(size==0) return -1;
	for(i=size-1;i>=0;i--){
		if(!isDigit((*(input_string+i)))) return -1;
		result+=(((int)(*input_string+i)-'0'))*(decimal);
		decimal*=10;
	}
	return result;
}

/*
 * input is a char.
 * returns 1 if char c contains an integer. 0 otherwise
 */

int isDigit(char c){
	if(((int)c >= (int)'0')&&((int)c <= (int)'9')) return 1;
	return 0;
}

