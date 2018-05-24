CC = gcc
COMP_FLAG = -ansi -Wall -Wextra \
-Werror -pedantic-errors
OBJS = main.o game.o mainAux.o parser.o solver.o
EXEC = sudoku

$(EXEC): $(OBJS)
	$(CC) -o $(EXEC) $(OBJS)
main.o: main.c mainAux.h game.h parser.h
	$(CC) $(COMP_FLAG) -c $*.c
game.o: game.c parser.h solver.h game.h solver.h
	$(CC) $(COMP_FLAG) -c $*.c
parser.o: parser.c parser.h
	$(CC) $(COMP_FLAG) -c $*.c
solver.o: solver.c solver.h game.h mainAux.h
	$(CC) $(COMP_FLAG) -c $*.c
mainAux.o: mainAux.c solver.h game.h parser.h
	$(CC) $(COMP_FLAG) -c $*.c
clean:
	rm -f $(OBJS) $(EXEC)
