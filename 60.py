#! /usr/bin/python

from math import *

def isPrime(n) :

    if n < 2 :
        return False

    if n % 2 == 0 :
        return False

    i = 3
    max = int(sqrt(n)) + 1
    while i <= max :
        if n % i == 0 :
            return False
        i += 2
        
    return True

def isConcatenatablePrime(a,b) :
    return isPrime(long(str(a)+str(b))) and isPrime(long(str(b)+str(a)))



triples = {
    1 : [],
    2 : [],
    3 : [],
    4 : [],
    5 : []
    }


a = 1
max = 100000000000
while a < max :

    if isPrime(a) :

        for triplelen in [5,4,3,2,1]:

            for triple in triples[triplelen] :
                
                isConcat = True
                for prime in triple :
                    if not isConcatenatablePrime(prime,a) :
                        isConcat = False
                        break

                if isConcat == True :
                    triples[triplelen+1].append(triple + [a])
                    if triplelen+1 == 4 :
                        print str(triples[triplelen+1][-1]) + "!!!!!!!"
                    elif triplelen+1 == 5 :
                        print ">>>> " + str(triples[triplelen+1][-1]) + " <<<<"
                        #assert 0

        
        triples[1].append([a])

    a += 2


print triples


