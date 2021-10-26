CFLAGS=-Wall -Wextra -pedantic -std=c99 
CC=clang $(CFLAGS)
OBJECTS = hatterspeak.o array.o bf.o bv.o hash.o ll.o parser.o speck.o



all		: hatterspeak

hatterspeak	: hatterspeak.o array.o bf.o bv.o hash.o ll.o parser.o speck.o
	$(CC) $(CFLAGS) -o hatterspeak hatterspeak.o array.o bf.o bv.o hash.o ll.o parser.o speck.o -lm

hatterspeak.o : hatterspeak.c
	$(CC) $(CFLAGS) -c hatterspeak.c 

array.o : array.h array.c
	$(CC) $(CFLAGS) -c array.h array.c 

bf.o : bf.h bf.c
	$(CC) $(CFLAGS) -c bf.h bf.c 

bv.o : bv.h bv.c
	$(CC) $(CFLAGS) -c bv.h bv.c 

hash.o : hash.h hash.c
	$(CC) $(CFLAGS) -c hash.h hash.c 
		
ll.o : ll.h ll.c
	$(CC) $(CFLAGS) -c ll.h ll.c 

parser.o : parser.h parser.c
	$(CC) $(CFLAGS) -c parser.h parser.c 

speck.o : speck.h speck.c
	$(CC) $(CFLAGS) -c speck.h speck.c 

clean	:
		rm -rf hatterspeak.o speck.o parser.o ll.o hash.o bv.o bf.o array.o bv.h.gch bf.h.gch array.h.gch hash.h.gch speck.h.gch hatterspeak parser.h.gch ll.h.gch infer-out

infer 	:
		make clean; infer-capture -- make; infer-analyze -- make