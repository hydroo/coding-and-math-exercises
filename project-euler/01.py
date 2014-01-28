#! /usr/bin/python

sum=0

for a in range(1000) :
	if a % 3 == 0 or a % 5 == 0 :
		sum += a

print sum

