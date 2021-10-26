CFLAGS=-Wall -Wextra -Werror -pedantic
CC=clang $(CFLAGS)
OBJECTS = sequence.o bv.o sieve.o




all		: sequence

sequence	: bv.o sequence.o sieve.o
	$(CC) $(CFLAGS) -o sequence sequence.o bv.o sieve.o -lm

sequence.o : sequence.c
	$(CC) $(CFLAGS) -c sequence.c 

bv.o : bv.h bv.c
	$(CC) $(CFLAGS) -c bv.h bv.c 
		
sieve.o : sieve.h sieve.c
	$(CC) $(CFLAGS) -c sieve.h sieve.c 

clean	:
		rm -rf sequence sequence.o bv.h.gch sieve.h.gch sieve.o bv.o infer-out

infer 	:
		make clean; infer-capture -- make; infer-analyze -- make

