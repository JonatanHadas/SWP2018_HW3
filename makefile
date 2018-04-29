CC = gcc

COMP_FLAG = -std=c99 -Wall -Wextra \
-Werror -pedantic-errors

EXEC = sudoku
OBJS = main.o parser.o solver.o game.o

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@
main.o: main.c parser.h solver.h game.h
	$(CC) $(COMP_FALG) -c $*.c
game.o: main.c parser.h solver.h game.h
	$(CC) $(COMP_FALG) -c $*.c
parser.o: main.c parser.h solver.h game.h
	$(CC) $(COMP_FALG) -c $*.c
solver.o: main.c parser.h solver.h game.h
	$(CC) $(COMP_FALG) -c $*.c
clean:
	rm -f $(EXEC) *.o