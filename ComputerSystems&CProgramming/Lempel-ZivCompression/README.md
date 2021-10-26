========== CSE 13 Fall 2020 =========     
Name: Mason Reali     
Collaborators: None    
Date: 12/13/2020       
Assignment 6: Create a program that uses the LZ87 compression algorithm to compress files
<=====================================>     
Files in Repository:       
	encode.c --> Driver code           
	word.c --> Contains code for word structs and wordtable    
	word.h --> Header      
	io.c --> Contains code for io    
	io.h --> Header      
	trie.c --> Contains code for trie      
	trie.h --> Header     
    code.h --> Header  
	Makefile --> To compile hatterspeak.c     
	DESIGN.pdf --> Gives psuedocode/basic layout of program        
<------------------------------------->    
How to use program:    
	After running make use command line arguments to call any of the functions,     
-i = Give file to read  
-o = Give file to Output    
-v = print stats    


   
Error Checking:    
If you input no arguments the program will return nothing     
If you input no i, the program will default to STDIN     
If you input no o, the program will default to STDOUT     
  


Errors make infer:      
	2 total      

	NULL_DEREFERENCE X 2   
		Make infer claims that the values coming from my trie structs at t->code could be infer, and are derefernced. This is true but i have a check to ensure that no NULL values slip through, if   t->code is ever NULL, the program will exit. These are both false flags.   
      
      
	

Sources:   
Lab provided psuedo-code 

Piazza for how to find bitlength of ints
 