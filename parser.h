#ifndef PARSER_H_
#define PARSER_H_

/**
 * parser Summary:
 *
 * The modul interprets user commands for the Sudoku games. Used by the main Aux and the game modules.
 *
 * get_command - parses the next move command by the user
 * get_number_from_string - parses a string containing a number into the number, for internal use.
 * read_num_fixed_cells - reads input from user on mumber of fixed cells when initializing a Sudoku game.
 */


/*
 * Assuming that result =/= NULL and contains space for 4 integers
 * ret[0] describes the command from user.
 * 1.set  2.hint  3.validate  4.restart  5.exit
 * in case of EOF uses exit command
 * when finished !=0 only commands 4.restart 5.exit are accepted
 * ret[1]-ret[3] are used for command parameters when needed
 */
int* get_command(int *result, int solved);

/*
 * gets an input string.
 * if string is empty or contains anything but numbers, return -1: Eror
 * returns the string parsed to an int number
 */
int get_number_from_string(char *input_string);

/*
 * param max number of fixed cells.
 * 0<=ret<max_cells when successful
 * ret =-1 if the function failed
 *
 * function read the input from the user if it's a valid number, returns it. If invalid number asks the user again.
 * If it's another input exits with an eror
 */
int read_num_fixed_cells(int max_cells);

#endif /* PARSER_H_ */
