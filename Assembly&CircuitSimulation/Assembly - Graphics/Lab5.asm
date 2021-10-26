##########################################################################
# Created by:  Reali, Mason
#              mreali
#              7 June 2020
#
# Assignment:  Lab 5: Functions and Graphics
#              CSE 012, Computer Systems and Assembly Language
#              UC Santa Cruz, Fall 2020
# 
# Description: This program is designed to print pixels using the bitmap tool in mars
# Notes:       This program is intended to be run from the MARS IDE. May take a few seconds for the program to finish running, be patient
#######################################################################

.macro push(%reg)
	subi $sp $sp 4
	sw %reg 0($sp)
.end_macro 

.macro pop(%reg)
	lw %reg 0($sp)
	addi $sp $sp 4	
.end_macro


.macro getCoordinates(%input %x %y)
 sll %y, %input, 16
 srl %y, %y, 16
 srl %x, %input, 16
 #sw %input , ($t0)
 #lb %y, ($t0)
 #lbu  %x, 2($t0)
.end_macro


.macro formatCoordinates(%output %x %y)
sll %output, %x, 16
add %output, %output, %y
 #la $t0, CordSort
 #sb %y , ($t0)
 #sb %x, 2($t0)
 #lw %output, ($t0)
.end_macro 

.macro cordToMem(%output %coords)
	li $t0, 0
	li $t1, 0		# x val hold
	li $t2, 128          	# y val mult/ hold
	li $t3, 0xffff0000
	getCoordinates(%coords $t0 $t1) # $t0 = x  $t1 = y
	mul  $t2, $t2, $t1
	add $t2, $t2, $t0
	mul $t2, $t2, 4
	add $t3, $t2, $t3
	la %output, ($t3)
.end_macro
















#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#  Subroutines defined below
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



#*****************************************************
# draw_pixel:
#  Given a coordinate in $a0, sets corresponding value
#  in memory to the color given by $a1	
#-----------------------------------------------------
#   Inputs:
#    $a0 = coordinates of pixel in format (0x00XX00YY)
#    $a1 = color of pixel in format (0x00RRGGBB)
#   Outputs:
#    No register outputs
#*****************************************************
draw_pixel: 
	cordToMem($t0 $a0)
	sw $a1, ($t0)
	jr $ra
	
#*****************************************************
# get_pixel:
#  Given a coordinate, returns the color of that pixel	
#-----------------------------------------------------
#   Inputs:
#    $a0 = coordinates of pixel in format (0x00XX00YY)
#   Outputs:
#    Returns pixel color in $v0 in format (0x00RRGGBB)
#*****************************************************
get_pixel: nop
	la $t0, 0
	cordToMem($t0 $a0)
	lw $v0, ($t0)
	jr $ra
#*****************************************************
#Clear_bitmap: Given a color, will fill the bitmap display with that color.
#   Inputs:
#    $a0 = Color in format (0x00RRGGBB) 
#   Outputs:
#    No register outputs
#    Side-Effects: 
#    Colors the Bitmap display all the same color
#*****************************************************
clear_bitmap: nop

	push($ra)
	la $a1, ($a0 ) 	# Storing the color we want in $t0
	li $t1, 0 	# Start at 0
	li $t2, 128	# 128
	li $t4, 0x00000000 	# x
	li $t5, 0xFFFFFFFF	# y
	li $t6, 0
	li $t7, 128
	
	
	loop:	# loop through Y coords
		beq $t1, $t2, fin2 	# loop condition
		li $t6, 0
		addi $t1, $t1, 1 
		addi $t5, $t5, 1
		li $t4, 0x00000000
		loop2:	# loop through X coords
			beq $t6, $t7, loop
			addi $t6, $t6, 1
			
			push($t0)
			push($t1)
			push($t2)
			push($t3)
			
			formatCoordinates($t3, $t4, $t5)
			la $a0, ($t3)
			jal draw_pixel
			
			pop($t3)
			pop($t2)
			pop($t1)
			pop($t0)
			
			addi $t4, $t4, 1
			j loop2
			
fin:	
	
	pop($t8)
	pop($t7)
	pop($t6)
	pop($t5)
	pop($t4)
	pop($t3)
	pop($t2)
	pop($t1)
	pop($t0)
	pop($ra)
	pop($s4)
	pop($s3)
	pop($s2)
	pop($s1)
	pop($s0)
	jr $ra
	
	
fin2:
	pop($ra)
	jr $ra	
	
#***********************************************
# draw_solid_circle:
#  Considering a square arround the circle to be drawn  
#  iterate through the square points and if the point 
#  lies inside the circle (x - xc)^2 + (y - yc)^2 = r^2
#  then plot it.
#-----------------------------------------------------
# draw_solid_circle(int xc, int yc, int r) 
#    xmin = xc-r
#    xmax = xc+r
#    ymin = yc-r
#    ymax = yc+r
#    for (i = xmin; i <= xmax; i++) 
#        for (j = ymin; j <= ymax; j++) 
#            a = (i - xc)*(i - xc) + (j - yc)*(j - yc)	 
#            if (a < r*r ) 
#                draw_pixel(x,y) 	
#-----------------------------------------------------
#   Inputs:
#    $a0 = coordinates of circle center in format (0x00XX00YY)
#    $a1 = radius of the circle
#    $a2 = color in format (0x00RRGGBB)
#   Outputs:
#    No register outputs
#***************************************************
draw_solid_circle: nop
	push($s0)
	push($s1)
	push($s2)
	push($s3)
	push($s4)
	la $s0, ($a0)
	push($ra)
	push($t0)
	push($t1)
	push($t2)
	push($t3)
	push($t4)
	push($t5)
	push($t6)
	push($t7)
	push($t8)
	li $t1, 0 	
	li $t2, 0	
	li $t4, 0	
	li $t5, 0	
	li $t6, 0
	li $t7, 0
	li $t8, 0
	getCoordinates($s0 $t0 $t3)
	sub $t1, $t0, $a1	#xmin
	add $t2, $t0, $a1	#xmax
	sub $t4, $t3, $a1	#ymin
	add $t5, $t3, $a1	#ymax
	add $t1, $t1, 0
	loopx:
		addi $t1, $t1, 1
		bgt $t1, $t2, fin 	# for (i = xmin; i <= xmax; i++) 
		sub $t4, $t3, $a1	# ymin 
		loopy:
			li $t6, 0
			li $t7, 0
			li $t8, 0
			bgt $t4, $t5, loopx	# for (j = ymin; j <= ymax; j++)
			addi $t4, $t4, 1
			
			sub $t6, $t1, $t0	# (i-xc)
			mul $t6, $t6, $t6	# (i-xc)(i-xc)
			sub $t7, $t4, $t3	# (j-yc)
			mul $t7, $t7, $t7	# (j-yc)(j-yc)
			add $t7, $t7, $t6	# (i - xc)*(i - xc) + (j - yc)*(j - yc) or a
			mul $t8, $a1, $a1	# r*r
			
			blt $t7, $t8, if
			j loopy
			if:
				push($a1)
				push($t0)
				push($t1)
				push($t2)
				push($t3)
				la $a1, ($a2)
				formatCoordinates($a0, $t1, $t4)
				jal draw_pixel
				pop($t3)
				pop($t2)
				pop($t1)
				pop($t0)
				pop($a1)
				j loopy
#***********************************************
# draw_circle:
#  Given the coordinates of the center of the circle
#  plot the circle using the Bresenham's circle 
#  drawing algorithm 	
#-----------------------------------------------------
# draw_circle(xc, yc, r) 
#    x = 0 
#    y = r 
#    d = 3 - 2 * r 
#    draw_circle_pixels(xc, yc, x, y) 
#    while (y >= x) 
#        x=x+1 
#        if (d > 0) 
#            y=y-1  
#            d = d + 4 * (x - y) + 10 
#        else
#            d = d + 4 * x + 6 
#        draw_circle_pixels(xc, yc, x, y) 	
#-----------------------------------------------------
#   Inputs:
#    $a0 = coordinates of the circle center in format (0x00XX00YY)
#    $a1 = radius of the circle
#    $a2 = color of line in format (0x00RRGGBB) 
#   Outputs:
#    No register outputs
#***************************************************				
draw_circle: nop
	push($s0)
	push($s1)
	push($s2)
	push($s3)
	push($s4)
	la $s3, ($a2)
	la $s4, ($a0)
	push($ra)
	push($t0)
	push($t1)
	push($t2)
	push($t3)
	push($t4)
	push($t5)
	push($t6)
	push($t7)
	push($t8)
	li $t0, 0
	li $t1, 0 	
	li $t2, 0
	li $t3, 3	
	li $t4, 0	
	li $t5, 0	
	li $t6, 0
	li $t7, 0
	li $t8, 0
				# $t0 = x
	la $t1 , ($a1)		# y = r
	mul $t2, $t1, 2		# 2 *r
	sub   $t4, $t3, $t2	#d = 3-2*r
	
	la $a1, ($s3)
	la $a2, ($t0)
	la $a3, ($t1)
	
	jal draw_circle_pixels
	while:
		blt $t1, $t0, fin
		addi $t0, $t0, 1
		li $t5, 0
		li $t6, 0
		bgt $t4, 0, ifOne
		j ifTwo
		ifOne:
			addi $t1, $t1, -1
			sub $t5, $t0, $t1	#(x-y)
			mul $t5, $t5, 4		#4 * (x-y)
			addi $t5, $t5, 10  	# 4* (x-y) +10
			add $t4, $t4, $t5	# d + 4 * (x-y) + 10
			la $a0, ($s4)
			la $a1, ($s3)
			la $a2, ($t0)
			la $a3, ($t1)
			jal draw_circle_pixels
			j while
		ifTwo:
			mul $t6, $t0, 4		# 4 * x
			addi $t6, $t6, 6	# 4 * x +6
			add $t4, $t4, $t6	# d + 4 * X + 6
			la $a0, ($s4)
			la $a1, ($s3)
			la $a2, ($t0)
			la $a3, ($t1)
			jal draw_circle_pixels
			j while
			
	
	jr $ra		
	
#*****************************************************
# draw_circle_pixels:
#  Function to draw the circle pixels 
#  using the octans' symmetry
#-----------------------------------------------------
# draw_circle_pixels(xc, yc, x, y)  
#    draw_pixel(xc+x, yc+y) 
#    draw_pixel(xc-x, yc+y)
#    draw_pixel(xc+x, yc-y)
#    draw_pixel(xc-x, yc-y)
#    draw_pixel(xc+y, yc+x)
#    draw_pixel(xc-y, yc+x)
#    draw_pixel(xc+y, yc-x)
#    draw_pixel(xc-y, yc-x)
#-----------------------------------------------------
#   Inputs:
#    $a0 = coordinates of circle center in format (0x00XX00YY)
#    $a1 = color of pixel in format (0x00RRGGBB)
#    $a2 = current x value from the Bresenham's circle algorithm
#    $a3 = current y value from the Bresenham's circle algorithm
#   Outputs:
#    No register outputs	
#*****************************************************
draw_circle_pixels: nop
	
	push($ra)
	push($t0)
	push($t1)
	push($t2)
	push($t3)
	push($t4)
	push($t5)
	push($t6)
	push($t7)
	push($t8)
	
	li $t0, 0
	li $t1, 0 	
	li $t2, 0
	li $t3, 0	
	li $t4, 0	
	li $t5, 0	
	li $t6, 0
	li $t7, 0
	li $t8, 0
	la $v0, ($a1)		   # load color
	getCoordinates($a0, $s0, $s1) # xc = s0     yc = s1
	li $t2, 0
	li $t3, 0
	add $t2, $a2, $s0          # xc+x   
	add $t3, $a3, $s1	   # yc+y
	formatCoordinates( $a0, $t2, $t3 )
	
	jal draw_pixel
	li $t2, 0
	li $t3, 0
	sub $t2, $s0, $a2          # xc-x   
	add $t3, $s1, $a3	   # yc+y
	formatCoordinates( $a0, $t2, $t3 )
	jal draw_pixel
	li $t2, 0
	li $t3, 0
	add $t2, $a2, $s0          # xc+x   
	sub $t3, $s1, $a3 	   # yc-y									
	formatCoordinates( $a0, $t2, $t3 )
	jal draw_pixel
	li $t2, 0
	li $t3, 0
	sub $t2, $s0 ,$a2         # xc-x   
	sub $t3, $s1, $a3	   # yc-y
	formatCoordinates( $a0, $t2, $t3 )
	jal draw_pixel
	li $t2, 0
	li $t3, 0
	add $t2, $a3, $s0	   # xc+y
	add $t3, $a2, $s1          # yc+x
	formatCoordinates( $a0, $t2, $t3 )
	jal draw_pixel
	li $t2, 0
	li $t3, 0
	sub $t2, $s0,  $a3         # xc-y        
	add $t3, $a2, $s1	   # yx+x
	formatCoordinates( $a0, $t2, $t3 )
	jal draw_pixel
	li $t2, 0
	li $t3, 0
	add $t2, $a3, $s0	   # xc+y
	sub $t3, $s1 ,  $a2        # yc-x
	formatCoordinates( $a0, $t2, $t3 )
	jal draw_pixel
	li $t2, 0
	li $t3, 0
	sub $t2,  $s0,	$a3   # xc-y
	sub $t3, $s1,  $a2         # yc-x
	formatCoordinates( $a0, $t2, $t3 )
	jal draw_pixel
	
	
	
	pop($t8)
	pop($t7)
	pop($t6)
	pop($t5)
	pop($t4)
	pop($t3)
	pop($t2)
	pop($t1)
	pop($t0)
	pop($ra)
	jr $ra
