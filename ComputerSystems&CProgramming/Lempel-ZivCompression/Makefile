CFLAGS=-Wall -Wextra -Wpedantic -Werror
CC=clang $(CFLAGS)
OBJECTS = decode.o encode.o trie.o word.o io.o




all		: encode decode

decode	: trie.o decode.o word.o io.o
	$(CC) $(CFLAGS) -o decode decode.o trie.o word.o io.o  -lm

encode	: trie.o encode.o word.o io.o
	$(CC) $(CFLAGS) -o encode encode.o trie.o word.o io.o  -lm

encode.o : encode.c code.h
	$(CC) $(CFLAGS) -c encode.c code.h

decode.o : decode.c code.h
	$(CC) $(CFLAGS) -c decode.c code.h

trie.o : trie.h trie.c
	$(CC) $(CFLAGS) -c trie.h trie.c 

word.o : word.h word.c 
	$(CC) $(CFLAGS) -c word.h word.c 

io.o : io.h io.c 
	$(CC) $(CFLAGS) -c io.h io.c 


		

clean	:
		rm -rf decode.o decode encode encode.o trie.h.gch trie.o code.h.gch io.o io.h.gch word.o word.h.gch infer-out

infer 	:
		make clean; infer-capture -- make; infer-analyze -- make
