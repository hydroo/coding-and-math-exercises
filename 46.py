#! /usr/bin/python

from math import *

def isPrime(num) :

    if num < 2 :
        return False

    for i in range(2,int(sqrt(num))+1) :
        if num % i == 0 :
            return False

    return True


primes = [2,3,5,7]

max = 1000000
a = 9
while a < max :

    #print a

    if isPrime(a) :

        primes.append(a)

    else :

        found = False

        for prime in primes :

            if a - prime != 0 and sqrt((a - prime)/2) % 1 == 0 :

                found = True
                break


        if found == False :

            print str(a) + "!!!!!!!!!!"


    a += 1

