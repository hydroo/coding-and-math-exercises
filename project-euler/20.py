#! /usr/bin/python

def fak(n) :
	if n > 0 :
		return n * fak(n-1)
	else :
		return 1

fak100 = str(fak(100))

sum = 0

for a in range(len(fak100)) :
	sum += int(fak100[a])

print sum

