

def inputReq():
	Height = int(input("Enter Desired Height:  "))
	check(Height)

def check(Height):
	if Height <= 0:
		print('Invalid')
		inputReq()
	if Height>0: 
		pattern(Height)

def pattern(x):
	row=0 #tells me what row im currently working on (first row is row 1)
	curNum=0 #Stores the current value for the number the for loops are working on
	for i in range (0,(x-1)+1):
		print('')
		row += 1

		for i in range (0,row): #Inserts the left half of the number triangle
			curNum += 1
			print(curNum ,end =  '	')

		for i in range (0,(((x-1)*2)+2)-(row*2)): #Inserts the '*' according to height of pattern given by user
			print('*',end = '	')
		tmp = 0

		for i in range (0,row): #Inserts the right half of the number triangle
			curNumN = curNum
			curNumN -= i
			print(curNumN ,end =  '	')

def main():
	inputReq()
	

main()








		
		
