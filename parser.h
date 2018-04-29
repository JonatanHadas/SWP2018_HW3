#ifndef _PARSER_H
#define _PARSER_H
/*
This module parses input into commands with parameters, and errors.
*/


typedef enum command_t{
	CMD_SET;
	CMD_HINT;
	CMD_VALIDATE;
	CMD_RESTART;
	CMD_EXIT;
	CMD_INVALID; /* used when an invalid command is entered */
} Command;

Command get_command();

#endif