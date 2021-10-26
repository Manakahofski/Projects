========== CSE 13 Fall 2020 =========     
Name: Mason Reali     
Collaborators: None    
Date: 11/30/2020       
Assignment 6: Create a program that enforces the queens newspeech laws using bloom filters and hash tables   
<=====================================>     
Files in Repository:       
	hatterspeak.c --> Driver code     
	hash.c --> Contains code for hash filter    
	hash.h --> Header     
	ll.c --> Contains code for linked list  
	ll.h --> Header    
	bv.c --> Contains code for bv  
	bv.h --> Header    
	array.c --> Contains code for array    
	array.h --> Header   
    bf.c --> Bloom Filter  
    bf.h --> Header
    parser.c --> for regex
    parcer.h --> Header
    speck.h --> Header
    speck.c --> for hash()
	Makefile --> To compile hatterspeak.c     
	DESIGN.pdf --> Gives psuedocode/basic layout of program      
	WRITEUP.pdf --> Answer to Writeup prompt   
<------------------------------------->    
How to use program:    
	After running make use command line arguments to call any of the   functions,   
-f = Bloom filte size  
-h = Hash table size  
-m = move to front rule  
-b = no move to front  
-s = show stats    

   
Error Checking:    
If you input no arguments the program will return nothing     
If you input no h, the program will default to 10000     
If you input no f, the program will default to 2^20     
  


Errors make infer:      
	8 total      

	NULL_DEREFERENCE X 4    
		While assigning values to an array at line 16 in shell.c infer errors and says that value could be null. Its not, the code works.    
    DEAD_STORE X 4   
        Values are not used when stats are not called, infer gets mad    

Memory Leaks:    
    Possible Memory leaks given by valgrind, not in all cases, at some point i gave up.      
	

Sources:   
For Array.h   
https://stackoverflow.com/questions/3536153/c-dynamically-growing-array  

For how to use a token to copy char* to char[] 
Code Credit edpresso  


	






git 