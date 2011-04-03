#! /usr/bin/python

squareofsums = 25502500
sumofsquares = 0


for a in range(1,101) :
	sumofsquares += a*a


print sumofsquares - squareofsums
print squareofsums- sumofsquares

