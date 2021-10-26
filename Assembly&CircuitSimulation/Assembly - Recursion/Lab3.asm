###################################################################################################################################################################
# Created by:   Reali, Mason
#		mreali
#		12 May 2020
#
# Assignment:   Lab 3: ASCII-risks
#               CSE 12, Computer Systems and Assembly Language
#               UC Santa Cruz, Spring 2020
#
# Description:  This program prints a pattern depending upon a given user input for the patterns height
#
# Notes: 	This program is intended to be run from the MARS IDE
####################################################################################################################################################################
# PYTHON PSUEDO-CODE
#
# def inputReq():
#	Height = int(input("Enter Desired Height:  "))
#	check(Height)
#
# def check(Height):
#	if Height <= 0:
#		print('Invalid')
#		inputReq()
#	if Height>0: 
#		pattern(Height)
#
# def pattern(x):
#	row=0 #tells me what row im currently working on (first row is row 1)
#	curNum=0 #Stores the current value for the number the for loops are working on
#	for i in range (0,(x-1)+1):
#		print('')
#		row += 1

#		for i in range (0,row): #Inserts the left half of the number triangle
#			curNum += 1
#			print(curNum ,end =  '	')

#		for i in range (0,(((x-1)*2)+2)-(row*2)): #Inserts the '*' according to height of pattern given by user
#			print('*',end = '	')
#		tmp = 0

#		for i in range (0,row): #Inserts the right half of the number triangle
#			curNumN = curNum
#			curNumN -= i
#			print(curNumN ,end =  '	')

# def main():
#	inputReq()
	
# main()
###################################################################################################################################################################################

#Start Assembly Code

.data
	prompt: .asciiz "Enter the height of the pattern(must be greater than 0):	"
	exit: .asciiz "Exiting Code"
	newline: .asciiz "\n"
	tab: .asciiz "	"
	inv: .asciiz "Invalid Entry!"
	
	
	
.macro invalid
li $v0, 4		# Prints the Error line
la $a0, inv
syscall
li $v0, 4		# Creates a new line
la $a0, newline  
syscall
j Input
.end_macro
		
	
	
	
.text
Input: 
	# Prompts user to input height
	li $v0, 4
	la $a0,prompt
	syscall

	# Ask for User Input
	li $v0,5
	syscall

	# Stores Result
	move $t0, $v0
	subi $t0, $t0, 1
	

	# Check if Height > 0
	bltz $t0, Branch2Macro
	


main:
# Loading registers for loop1 Range(0,Height+1)
li $s1, 0 
la $s2, ($t0)
addi $s2, $s2, 1

# Loading registers for loop2 Range(0, row)
li $s3, 0 

# Loading registers for loop3 Range(0,((x*2)+2)-(row*2))
li $s5, 0

# Loading register for loop4 Range(0,row)
li $s7, 0

# Holding the CurNum Variable
li $t2, 0

# Prints a new row and adds 1 to row variable
Loop1:
	beq $s2, $s1, Exit      # for i in range (0,height+1):
	addi $s1, $s1, 1 
	addi $t1, $t1, 1        # $t1 = row
	li $v0, 4		# Creates a new line
	la $a0, newline                           
	syscall
	addi $s4, $s4, 1
	li $s3, 0 		# Sets Loop2 Range back to (0,row)
	j Loop2
	
# Inserts the left half of the number triangle	
Loop2:  
	beq $s3, $s4, Loop3 	# for i in range (0,row):
	addi $s3, $s3, 1
	addi $t2, $t2, 1
	li $v0, 1 
	la $a0, ($t2)		# Prints value of CurNum
	syscall
	li $v0, 4
	la $a0, tab
	syscall			
	la $s6, ($t0)		# Setting up the next loops range
	mul $s6, $s6, 2
	addi $s6, $s6, 2
	la $t3, ($t1)       	# Assign t3 with row
	mul $t3, $t3, 2
	sub $s6, $s6, $t3
	li $s5, 0
	j Loop2
	
	
# Inserts the correct amount of * in between the two number triangles	
Loop3:
	li $s7, 0		# Resets Loop4 range 
	beq $s5, $s6, Loop4	# for i in range ((0,(((x-1)*2)+2)-(row*2))
	addi $s5, $s5, 1
	li $v0, 11		# Prints *
	li $a0, 42
	syscall
	li $v0, 4		
	la $a0, tab
	syscall
	
	j Loop3
	
	
	
# Inserts the right side number triangle	
Loop4:
	beq $s7, $s4, Loop1	# for i in range(0,row)
	la $t4, ($t2)		# Temp val to reverse number order
	sub $t4, $t4, $s7	# Revereses order of numbers, ie: 1 2 3 ---> 3 2 1
	addi $s7, $s7, 1
	li $v0, 1		# Prints Numbers
	la $a0, ($t4)
	syscall
	li $v0, 4
	la $a0, tab
	syscall
	j Loop4
	
	
	
# Makes one least NewLine then exits code
Exit:
	li $v0, 4
	la $a0, newline                           
	syscall
	li $v0, 10
	syscall
	
# I couldnt figure out how to branch to a macro so i did this LOL	
Branch2Macro:
	invalid
	
	
	
	
