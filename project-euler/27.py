#! /usr/bin/python

from math import sqrt

def prime(n) :

	if n < 2 :
		return False

	for i in range(2,int(sqrt(n))+1) :
		if n % i == 0 :
			return False
	return True

aa = 0
bb = 0
cc = 0


for a in range(-999,1000,2) :

	for b in range(-999,1000,2) :

		c = 0

		for n in range(0,1000) :
			if prime(n*n+a*n+b) == True :
				c = c + 1

		if c > cc :
			aa = a
			bb = b
			cc = c
			print aa,bb,cc


	print a

