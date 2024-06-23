CC = gcc
FLAGS = -Wall -Wextra
OBJ = matrix.o stack.o main.o 

automaton : $(OBJ)
	$(CC) $(FLAGS) -o $@ $^

main.o : main.c stack.h matrix.h
	$(CC) $(FLAGS) -o $@ -c $<

matrix.o : matrix.c matrix.h
	$(CC) $(FLAGS) -o $@ -c $<

stack.o : stack.c stack.h
	$(CC) $(FLAGS) -o $@ -c $<

clean :
	rm -rf *.o