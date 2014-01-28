#! /usr/bin/python

i = 1
triangle = 0
numdivisors = 0

while True :
	triangle += i
	numdivisors = 0

	print triangle
	
	for a in range(1,triangle+1) :
		if triangle % a == 0 :
			numdivisors = numdivisors + 1
			print " i%d: %d" % (numdivisors, a)

	if numdivisors > 500 :
		break

	i = i + 1
