========== CSE 13 Fall 2020 =========     
Name: Mason Reali     
Collaborators: None    
Date: 11/15/2020     
Assignment 5: Create a program that can sort a randomly generated array using Shell, Quick, Bubble   
and BinaryInsertion sorts.   
<=====================================>     
Files in Repository:       
	sorting.c --> Driver code     
	bubble.c --> Contains code for bubble sort    
	bubble.h --> Header     
	quick.c --> Contains code for quick sort   
	quick.h --> Header    
	shell.c --> Contains code for shell sort   
	shell.h --> Header    
	binary.c --> Contains code for binary sort   
	binary.h --> Header    
	Makefile --> To compile sequence.c     
	DESIGN.pdf --> Gives psuedocode/basic layout of program      
	WRITEUP.pdf --> Answer to Writeup prompt   
<------------------------------------->    
How to use program:    
	After running make use command line arguments to call any of the   functions,   
-A = Run all sorts  
-p(n) = print n elements of array  
-n(l) = array of length l  
-r(s) = seed srand()  
-s = shell sort   
-b = bubble sort   
-i = binary insertion sort   
-q = quick sort   
   
Error Checking:    
If you input no arguments the program will return nothing   
If you input no n, the program will default to 100   
If you input no p, the program will default to 100   
If you input no r, the program will default to 8222022   
If p>n, An error message will pop up   
if n=0, An error message will pop up   

Errors make infer:   
	3 total   

	NULL_DEREFERENCE
		While assigning values to an array at line 16 in shell.c infer errors and says that value could be null. Its not, the code works.
	NULL_DEREFERENCE
		While assigning values to an array at line 103 in sorting.c infer errors and says that value could be null. Its not, the code works.
	DEAD_STORE
		Claims that a bool change to true in case 'p' is never used, which is only true if the user doesnt input -p. This is intended in order to not print if the user doesnt ask it to print

Sources:   
Only lab document for psuedo code of all sorts   


	






git 