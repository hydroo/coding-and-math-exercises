#! /usr/bin/python

def fac(n) :
	ret = 1
	while n > 1 :
		ret = ret * n
		n = n - 1

	return ret

sum = 0

a = 3
# while a < 1000000000 :
while a < 10000000 :

	aa = str(a)

	aasum = 0

	i = 0
	while i < len(aa) :
		aasum = aasum + fac(int(aa[i]))
		i = i + 1

	if aasum == a :

		sum = sum + a

		print a

	a = a + 1
