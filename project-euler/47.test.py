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
    for prime in primes :

        while rest % prime == 0 :

            if ret.has_key(prime) == False :
                ret[prime] = 0

            ret[prime] += 1
        
            rest /= prime

    assert rest == 1

    return ret


pos = 0
#fournumbers = [{},{},{},{}]
#fournumbers = [{1:1,2:2,3:3,4:4},{5:5,6:6,7:7,8:8},{9:9,10:10,11:11,12:12},{13:13,14:14,15:15,16:16}]
fournumbers = [{1:1,2:2,3:3,4:4},{6:6,7:7,8:8},{9:9,10:10,11:11,12:12},{13:13,14:14,15:15,16:16}]
primes = []
max = 4
a = 0
skip = 3

while a < max :

    print a

    if isPrime(a) :
        primes.append(a)

#    print str(a) + "   " + str(primeFactors(a,primes))

    #fournumbers[pos] = primeFactors(a,primes)

    if len(fournumbers[pos]) != 4 :

        skip = 0

    elif skip < 3 :

#        print str(a) + str(fournumbers)

        skip += 1 

    else :

        allFactors = {}
        expectedSize = 0
        for factors in fournumbers :
            expectedSize += len(factors)
            for factor in factors :
                allFactors[factor] = 1

        if expectedSize == len(allFactors) :

            print str(a) + "   " + str(fournumbers) + "    !!!!!!!!!!!!!!!!!!!"

    #print fournumbers

    pos = (pos + 1) % 4
    a += 1

