#! /usr/bin/python

a = 1
evenlydivisible = 0
while True :
	
	found = True
	for div in [11,12,13,14,15,16,17,18,19,20]:
		if a % div != 0 :
			found = False
			break

	if found == True :
		break

	a=a+1

print a

