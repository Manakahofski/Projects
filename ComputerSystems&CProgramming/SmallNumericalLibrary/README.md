========== CSE 13 Fall 2020 =========  
Name: Mason Reali  
Collaborators: None  
Date: 10/24/2020  
Assignment 2: Approximate Sin, Cos, Tan, and Exp using taylor series and compare against 
the math.h functions  
<=====================================>  
Files in Repository:  
	math.c --> Driver code for C  
	Makefile --> To compile lrc.c  
	DESIGN.pdf --> Gives psuedocode/basic layout of program  
	WRITEUP.pdf --> Pre-Lab questions 
<------------------------------------->  
How to use program:  
	After running make use command line arguments to call any of the functions, -s for Sin, -c for Cos, -t for Tan,
	 -a for all of them at once

Error Checking: 
If you input no arguments the program will end and prompt "An argument must be supplied".
If you input more than one argument it will end and prompt "Only one argument allowed".

Errors make infer:
	2 Total
1.	"int n = 1 line 126 never used" 
	This is a necassary value to initialize n for the while loop that looks for when the term is below epsilon in
	the Exp function

2.	"double val = 1 line 125 never used"
	This is a necassary value to initialize val for the while loop that looks for when the term is below epsilon in
	the Exp function





