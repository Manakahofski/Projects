##########################################################################
# Created by:  Reali, Mason
#              mreali
#              24 May 2020
#
# Assignment:  Lab 4: Sorting Integers
#              CSE 012, Computer Systems and Assembly Language
#              UC Santa Cruz, Fall 2020
# 
# Description: This program takes in Hexadecimal values as program arguments and converts them to integers and then sorts the list from least
# 		to greatest
# Notes:       This program is intended to be run from the MARS IDE. May take a few seconds for the program to finish running, be patient
##########################################################################
#Python Psuedo-Code
#import sys

#def convertHexToDec(x):
#	HexValIn = []
#	for i in range(2,len(x)):		# Deletes 0x
#		HexValIn.append(x[i])
#	total = 0    # Holds Total For Hex Input In Decimal
#	key = ['0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F','G']   #ASCII TO HEX
#	y = -1       # Stores What Square Im On
#	for i in range(len(HexValIn)-1,-1,-1):
#		y+=1
#		Hex = HexValIn[i]
#		Dec = key.index(Hex)
#		total = total + (Dec *(16 ** y))
#	return total 
#
#def bubble_sort(nums):	# Taken From stackabuse.com
    # We set swapped to True so the loop looks runs at least once
 #   swapped = True
  #  while swapped:
   #     swapped = False
    #    for i in range(len(nums) - 1):
     #       if nums[i] > nums[i + 1]:
      #          # Swap the elements
       #         nums[i], nums[i + 1] = nums[i + 1], nums[i]
        #        # Set the flag to True so we'll loop again
         #       swapped = True
#    return nums
#def main():
#	pushValues()
#	print("Integer values:")
#	print(IntList)
#	print('Sorted values:')
#	print(bubble_sort(IntList))
#
#pushValues():
#	IntList = []
#	HexList = []
#	for i in range(1, len(sys.argv)):	# Puts Hex Values Into HexList
#		HexList.append(sys.argv[i]) 
#	for i in range(0,len(HexList)):		# Splits Values up into list of Characters
#		HexVal = list(HexList[i])
#		IntList.append(convertHexToDec(HexVal))
#
#main()
			

###############################################################################################################################################################################################
# Mips code starts here
.data 
	IntList: .space 200
	SortList:.space 200
	sort: .asciiz "Sorted values:\n"
	spaces: .asciiz " "
	pa: .asciiz "Program arguments:\n"
	newL: .asciiz "\n"
	int: .asciiz "Integer values:\n"

.text



main:
	la $s3, ($a0)
	jal init
	jal startUp
	jal progArgs
	jal init     #dont change k0 or t0 , t3 = 16
	jal ProgPush
	jal init2
	jal ReadTime
	j SortArray
			
init2:
	li $v0, 4
	la $a0, newL
	syscall
	la $a0, newL
	syscall
	li $v0, 4 
	la $a0, int
	syscall
	li $t1, 0	
	li $t2, 0
	li $t3, 16
	li $t4, 0
	li $t5, 0
	li $t7, 0
	li $s1, 0
	li $s2, 0
	li $s4, 0
	li $s5, 0
	li $s6, 0
	
	li $s4, 0
	mul $k1, $k1, 1
	#add $t0, $t0, $s6
	jr $ra
	
					
						
								
# Initializes Registers 
init:
	la $s5, IntList
	la $s6,($s5)
	la $t8, ($s3)
	la $s2, ($a1)
	li $t6, 5
	li $t7, 0
	jr $ra
# End Init
	
# prints Prompts	
startUp:
	la $t8, ($a0)
	li $v0, 4
	la $a0 , pa
	syscall
	
# End Startup			
			
	
# Prints The Program Arguments									
progArgs:
	
	beq $t7 , $t8 , return 	# Loop
	
	li $t5, 0
	addi $t7, $t7, 1
	beq $t7 , 1 , char
	li $v0, 4
	la $a0 , spaces
	syscall
	addi $a1, $a1, 4
	la $s2, ($a1)
	
char:
	#Inside Loop Reads Charactars
	lw $t4, ($s2)		# Loads PA Location
	addi $t4, $t4, -1
	beq $t5 , $t6 , progArgs 	# Loop
	lb $a0, ($t4)		# Increments byte by 1
	addi $t5, $t5, 1
	add $t4, $t4, $t5	# Sets $T4 to new byte location
	lb $a0, ($t4)
	li $v0 , 11
	syscall
	j char
	
return: 
	jr $ra
	
# End Of Program Prints






# Pushes Program Arguments Through Converter To Add to Array
ProgPush: 
	la $s4, ($ra)
	
progPush:
	beq $t7 , $t8 , returnOne 	# Loop
	li $t5, 0
	addi $t7, $t7, 1  #IMPLEMENT SOME SORT OF ARRAY FUNCTION HER MAONSSON
	beq $t7 , 1 , charOne
	addi $s2, $s2, -4
	
	
charOne:
	#Inside Loop Reads Charactars
	lw $t4, ($s2)		# Loads PA Location
	addi $t4, $t4, -1
	beq $t5 , $t6 , progPush 	# Loop
	lbu $a0, ($t4)		# Increments byte by 1
	addi $t5, $t5, 1
	add $t4, $t4, $t5	# Sets $T4 to new byte location
	lbu $a0, ($t4)
	jal asciiToHex
	addi $t0 , $t0 , 4
	
	j charOne
	
returnOne: 
	jr $s4


# Convert Ascii Hex String Garbage To Proper Hex

asciiToHex:
        addi $k0, $k0, 1
	li $t2 , 0x30 # Ascii 0
	li $t3 , 0x39 #Ascii 9
	la $s1, ($ra) # Store Return Adress To $S1
	
	blt $a0 , 0x30, yeet
	bgt $a0, $t3, letter
	jal number
	jr $s1
number:
	addi $a0, $a0, -0x30
	li $v0, 1
	
	sw $a0, IntList($t0)
	add $s7, $s7, $a0
	
	jr $ra									#flip stack reading, use x to find length
	
letter:
	beq $a0, 'x', check
	addi $a0, $a0, -0x37
	li $v0, 1
	
	sw $a0, IntList($t0)
	add $s7, $s7, $a0
	
	jr $s1
check:
	sw $a0, IntList($t0)
	jr $s1
yeet:
	addi $k1 , $k1, 1
	addi $t0 , $t0 , -4
	jr $s1
	
# End Of Convert Function	

# Convert 2 Electric boogaloo
isX:
	beq $t1, 'x', r
	jr $ra
r:
	li $t4, -1
	li $v0, 1
	la $a0, ($s2)
	sw $s2, SortList($t7)
	addi $t7, $t7, 4
	syscall
	li $s2, 0
	li $v0, 4
	la $a0 , spaces
	syscall
	j ReadTime
is0:
	bgt $t2, 0, r1
	addi $t2, $t2, 1
	jr $ra
r1:
	jr $ra
is32:
	blt $t2, 32, r1
	li $t2, 256
	jr $ra
save:
	la $s5, ($ra)
	addi $s6, $s6, 1
ReadTime:
	beq $s6, 0, save
	beq $s0, $k0, done     #dont change k0 or t0 , t3 = 16
	addi $t0, $t0, -4 	# t0 = current location 
	lw $t1, IntList($t0)		 
	jal isX
	mul $t2, $t3, $t4     # t2 = current power , t3 = 16 , t4 = current num
	jal is0
	jal is32
	mul $s1, $t1, $t2
	add $s2, $s2, $s1
	addi $s0 , $s0, 1
	addi $t4, $t4, 1    
	j ReadTime
done:
	jr $s5
	# Sort through the array using a bubble style technique
SortArray:
	mul $t0, $s3, 4		#$t0 know the secrets
	la $s0, SortList        #s0 will hold my strat
	la $s1, SortList($t0)   #s1 will hold the end
OutofdeLoop:    # Thanks textbook
	la $k0, ($s0)
	li $t1, 1
IndeLoop:
	addi $s7, $s7, 1  # i give up trying to be fancy it gets 1000 chances to sort lol
	lw $s2, ($k0)  # First var
	lw $s4, 4($k0) # Second var
	blt $s2, $s4, sorte
	li $t1, 0
	sw $s4, ($k0) #Switched if needed sorting
	sw $s2, 4($k0)
sorte:
	addi $k0, $k0, 4
	bgt $s7, 1000, init3
	bne $k0, $s1, IndeLoop # Continues Switching
	bne  $t1, 1, OutofdeLoop # Supposed to stop sorting when sorted but i couldnt get it to work so


# Resets Registers
init3:
	li $v0, 4
	la $a0, newL
	syscall
	la $a0, newL
	syscall
	li $t0, 0
	li $t1, 0
	li $t2, 0
	li $v0, 4
	la $a0, sort
	syscall
# Prints Sorted Values Array	
print:
	beq $t0, $s3, die
	addi $t2, $t2, 4
	lw $a0, SortList($t2)
	
	addi $t0, $t0,1
	li $v0, 1
	syscall
	li $v0, 4
	la $a0, spaces
	syscall
	j print
# Represents how i felt after this lab
die:
	la $a0, newL
	syscall
	
	li $v0, 4
	la $a0, newL
	li $v0, 10
	syscall

