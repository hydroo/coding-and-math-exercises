#! /usr/bin/python

palindrome = 0

for a in range(1000) :
	for b in range(1000) :
		prod = a*b
		str = '%(prod)d' % {'prod' : prod}

		ispal = True
		for i in range(len(str)/2) :
			if str[i] != str[-(i+1)] :
				ispal = False
				break

		if ispal == True and palindrome < prod :
			palindrome = prod

print palindrome
