#! /usr/bin/python

sumsum = 0

for a in range(2,10000000) :

	t = str(a)
	sum = 0

	for i in range(len(t)) :
		sum = sum + int(t[i])**5

	if sum == a :

		sumsum = sumsum + sum

		print a

print sumsum

