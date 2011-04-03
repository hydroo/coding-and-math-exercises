#! /usr/bin/python

a = str(2**1000)

sum = 0

for b in range(len(a)) :
	sum += int(a[b])

print sum

