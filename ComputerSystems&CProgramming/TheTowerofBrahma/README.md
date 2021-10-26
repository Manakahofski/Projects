========== CSE 13 Fall 2020 =========  
Name: Mason Reali  
Collaborators: None  
Date: 11/1/2020  
Assignment 3: Create a program to solve Hanoi both iterativly and recursivly  
<=====================================>  
Files in Repository:  
	tower.c --> Driver code for C 
	stack.c --> Contains basic Stack managment function
	stack.h --> Header 
	Makefile --> To compile lrc.c  
	DESIGN.pdf --> Gives psuedocode/basic layout of program  
	WRITEUP.pdf --> Pre-Lab questions 
<------------------------------------->  
How to use program:  
	After running make use command line arguments to call any of the functions, 
-r for recursive, -s for stack method, and -nx to pick number of Disks

Error Checking: 
If you input no arguments the program will return nothing
If you input no number of disks, the program will default to 5

Errors make infer:
	2 Total
1.	error: MEMORY_LEAK 
	Valgrind finds no memory leak, this is a false positive

2.	NULL_DEREFERENCE 
	Renamed capacity to size in stack create for ease of reading, infer doesnt like that.

Sources:
Help for recursive function from a video studying recursive stratagies in python
	https://www.youtube.com/watch?v=rf6uf3jNjbo

Stack logic from Lectures 




