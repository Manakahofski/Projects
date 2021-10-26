CFLAGS=-Wall -Wextra -Werror -pedantic -std=c99
CC=clang $(CFLAGS)
OBJECTS = sorting.o bubble.o shell.o quick.o binary.o



all		: sorting

sorting	: sorting.o bubble.o shell.o quick.o binary.o
	$(CC) $(CFLAGS) -o sorting sorting.o bubble.o shell.o quick.o binary.o -lm

sorting.o : sorting.c
	$(CC) $(CFLAGS) -c sorting.c 

bubble.o : bubble.h bubble.c
	$(CC) $(CFLAGS) -c bubble.h bubble.c 
		
shell.o : shell.h shell.c
	$(CC) $(CFLAGS) -c shell.h shell.c 

quick.o : quick.h quick.c
	$(CC) $(CFLAGS) -c quick.h quick.c 

binary.o : binary.h binary.c
	$(CC) $(CFLAGS) -c binary.h binary.c 

clean	:
		rm -rf sorting.o bubble.o shell.o quick.o binary.o binary.h.gch bubble.h.gch sorting shell.h.gch quick.h.gch infer-out

infer 	:
		make clean; infer-capture -- make; infer-analyze -- make




