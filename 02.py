#! /usr/bin/python

sum = 0
fibonacci = [1,2]

while 1 :
	newfibonacci = fibonacci[-1]+fibonacci[-2]
	if newfibonacci > 1000000 :
		break
	fibonacci.append(newfibonacci)	

for a in fibonacci :
	if a % 2 == 0 :
		sum += a
	
print sum

