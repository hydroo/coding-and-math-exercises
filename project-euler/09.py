#! /usr/bin/python

import math

prod = 0

b = 0
c = 0
a = 1
while a < 1001 :
	b = 1
	while b < 1001 :
		c = math.sqrt(a*a + b*b)
		if (a + b + c) == 1000 :
			prod = a*b*c
			break
		b = b + 1
	
	a = a + 1

	if prod != 0 :
		break

#print a
#print b
#print c
#print a+b+c
print prod

