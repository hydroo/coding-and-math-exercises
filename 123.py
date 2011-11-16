#! /usr/bin/env python

from math import *

def isPrime(n) :

	if n < 2 :
		return False

	if n == 2 :
		return True

	if n % 2 == 0 :
		return False

	i = 3
	max = int(sqrt(n)) + 1
	while i <= max :
		if n % i == 0 :
			return False
		i += 2
		
	return True


i = 1
n = 0
min = 21000
max = 100000000000
while n <= max :

	i += 1

	if isPrime(i) == False :
		continue

	n += 1

	if n < min :
		continue

	print n, i, ((i-1)**n + (i+1)**n) % (i*i)
	
	if ((i-1)**n + (i+1)**n) % (i*i) > 10**10 :
		assert False



