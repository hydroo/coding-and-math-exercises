#! /usr/bin/python

prods = {}
a = 1
while a < 987654322 :

	b = a+1
	while b < 987654322 :

		prod = a * b

		identity = str(a)+str(b)+str(a*b)

		identitylen = len(identity)

		if identitylen > 9 :
			break
		elif identitylen == 9 :
			digits = {}
			for i in range(9) :
				digits[int(identity[i])] = 1

			if len(digits) == 9 and not digits.has_key(0):
				prods[a*b] = [a,b]

				print str(a)+","+str(b)+"="+str(a*b)

		b = b + 1


	a = a + 1


sum = 0
for a in prods.keys() :
	sum += a

print sum

