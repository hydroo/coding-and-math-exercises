#! /usr/bin/python

import math


def isPrime(n) :

	a = 2
	end = int(math.sqrt(n))
	while a <= end :
		if n % a == 0 :
			return False
		a = a + 1

	return True

def rotations(n) :

	ret = []

	nm = str(n)

	a = 0
	while a < len(nm) :

		rot = ""

		b = 1
		while b < len(nm) :
			rot += nm[b]
			b = b + 1
		rot += nm[0]

		nm = rot

		ret.append(int(rot))

		a = a + 1


	return ret



primes = {}

a = 2
# while a < 1000000 :
while a < 1000000 :

	if isPrime(a) :

		nm = str(a)

		couldbe = True
		i = 0
		while i < len(nm) :
			if int(nm[i]) % 2 == 0 :
				couldbe = False
				break
			i = i + 1

		if couldbe :

			primes[a] = True

			for rot in rotations(a) :
				if not primes.has_key(rot) :
					primes[rot] = False

	print a
	
	a = a + 1


# would have been omitted -> insert it by hand ;)
primes[2] = True



correctprimes = {}

for b in primes.keys() :

	if primes[b] == True :

		isprime = True

		for c in rotations(b) :
			if primes[c] == False :
				isprime = False
				break

		if isprime == True :
			correctprimes[b] = 1

print "---correct primes---"
for c in correctprimes.keys() :
	print c

print "number of circular primes: "+str(len(correctprimes))

