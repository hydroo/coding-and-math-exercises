#! /usr/bin/env python3

from math import *


minD = 2
maxD = 1000


def isSquare(a) :
	return sqrt(a) == float(floor(sqrt(a)))


def continuedFraction(a, pos, dSquaredFloorTimesTwo, chain) :

	# manual tailrecursion
	while True :

		aFloor = floor(a)

		if dSquaredFloorTimesTwo == aFloor and pos % 2 == 0 :
			return chain

		a = 1.0/(a-aFloor)
		pos += 1
		chain += [aFloor]


def continuedFraction2(S, pos, dSquaredFloorTimesTwo, chain) :

	m = 0
	d = 1
	a = floor(sqrt(S))

	chain = [a]

	# manual tailrecursion
	pos = 1
	while True :

		m = d*a - m
		d = (S - m**2) / d
		a = floor((sqrt(S) + m) / d)

		if dSquaredFloorTimesTwo == a and pos % 2 == 0:
			return chain

		chain.append(a)


		pos += 1


def rationalFromContinuedFraction(chain) :

	numerator = 1
	denominator = chain[len(chain)-1]

	i = len(chain)-1
	while i > 0 :

		newDenominator = chain[i-1]*denominator+numerator
		newNumerator = denominator

		denominator = newDenominator
		numerator = newNumerator

		i -= 1

	return denominator, numerator


def forEachD(D) :

	cFrac = continuedFraction2(D, 0, 2*floor(sqrt(D)),[])

	x, y = rationalFromContinuedFraction(cFrac)

	return (D,x, y)


largestX = (0,0,0)

D = minD
while D <= maxD :

	if isSquare(D) :
		D += 1
		continue

	ret = forEachD(D)

	#print(ret)

	if ret[1] > largestX[1] :
		largestX = ret
		print(largestX[0])
		#print(largestX)

	D += 1

