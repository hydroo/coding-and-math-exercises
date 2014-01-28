#! /usr/bin/python

set = {}

for a in range(2,101) :
	for b in range(2,101) :
		set[a**b] = 1

print len(set)

