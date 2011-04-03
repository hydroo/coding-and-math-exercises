#! /usr/bin/python

from math import *

def isPrime(num) :

    if num < 2 :
        return False

    for i in range(2,int(sqrt(num))+1) :
        if num % i == 0 :
            return False

    return True


primes = {2 : 1}
primesl = [2]


# get all primes below 1 mio
a = 3
while a < 1000000 :

    if isPrime(a) == True :

        primes[a] = 1
        primesl.append(a)

    a += 2


#print primes
#print len(primes)

bestsum = 0
bestcount = 0
start = 0
primescount = len(primes)
while start < primescount :

    sum = 0
    count = 0

    end = start
    while end < primescount :

        sum += primesl[end]
        count += 1

        if primes.has_key(sum) == True :

            if bestcount < count :
                bestcount = count
                bestsum = sum
                print str(count) + "  " + str(sum)


        end += 1

    start += 1

print "bestcount " + str(bestcount)
print "bestsum " + str(bestsum)

