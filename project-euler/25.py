#! /usr/bin/python

def fib_loop() :

	pre = 1
	prepre = 0
	tmp = 0
	i = 0

	while len(str(tmp)) < 1000 :
		tmp = prepre
		prepre = pre
		pre = tmp+pre
		#print i, tmp
		i = i + 1


	print i
	print tmp
	print len(str(tmp))


import sys

print "fib_loop: ", fib_loop()
