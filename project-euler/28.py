#! /usr/bin/python

sum = 1

starts = [(3,10),(5,12),(7,14),(9,16)]

def calc(start,startstep,increase,length) :

	ret = start

	step = startstep

	for a in range(length) :

		start = start + step
		step = step + increase
		ret = ret + start

	return ret

for a in starts :

	ret = calc(a[0],a[1],8,500-1)
	sum = sum + ret
	print ret

print sum

