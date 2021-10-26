CFLAGS=-Wall -Wextra -Werror -pedantic
CC=clang $(CFLAGS)
OBJECTS = tower.o stack.o 




all		: tower

tower	: stack.o tower.o
	$(CC) $(CFLAGS) -o tower tower.o stack.o -lm

tower.o : tower.c
	$(CC) $(CFLAGS) -c tower.c 
		
stack.o : stack.h stack.c
	$(CC) $(CFLAGS) -c stack.h stack.c 

clean	:
		rm -rf tower tower.o stack.h.gch stack.o infer-out

infer 	:
		make clean; infer-capture -- make; infer-analyze -- make

