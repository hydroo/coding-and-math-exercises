#! /usr/bin/python

from math import *


def isPrime(num) :

    if num < 2 :
        return False

    for i in range(2,int(sqrt(num))+1) :
        if num % i == 0 :
            return False

    return True

def primeFactors(n,primes) :

    ret = {}

    rest = n
    a = 0
    max = len(primes)
    while primes[a] <= rest:

        while rest % primes[a] == 0 :

            if ret.has_key(primes[a]) == False :
                ret[primes[a]] = 0

            ret[primes[a]] += 1
        
            rest /= primes[a]

        a += 1

    assert rest == 1

    return ret


pos = 0
fournumbers = [{},{},{},{}]
primes = []
max = 10000000000
a = 2
skip = 3

while a < max :

    if a % 200000 == 0 :

        print a

#    print str(a) + "   " + str(primeFactors(a,primes))


    if isPrime(a) :

        primes.append(a)
        skip = 0

#        print "prime  " + str(a)

    else :

        fournumbers[pos] = primeFactors(a,primes)
        
        if len(fournumbers[pos]) != 4 :

            skip = 0
#            print "- " + str(a) + "  " + str(len(fournumbers[pos]))

        elif skip < 3 :

    #        print str(a) + str(fournumbers)
#            fournumbers[pos] = primeFactors(a,primes)
#            print str(a) + "  " + str(len(fournumbers[pos]))

            skip += 1 

        else :

 #           fournumbers[pos] = primeFactors(a,primes)
#            print str(a) + "  " + str(len(fournumbers[pos]))

    #        allFactors = {}
    #        expectedSize = 0
    #        for factors in fournumbers :
    #            expectedSize += len(factors)
    #            for factor in factors.keys() :
    #                allFactors[factor**factors[factor]] = 1

    #        if expectedSize == len(allFactors) :

            print str(a) + "   " + str(fournumbers) + "    !!!!!!!!!!!!!!!!!!!"

    #print fournumbers

    pos = (pos + 1) % 4
    a += 1

