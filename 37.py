#! /usr/bin/python

from math import *

def isPrime(num) :

    if num < 2 :
        return False

#    if (2**(num-1))%num != 1 :
#        return False

    for a in range(2,int(sqrt(num))+1) :
        if num % a == 0 :
            return False

    return True


def truncatablePrime(n) :
    
    s= str(n)
    l = len(s)

    if isPrime(n) == False :
        return False


    for a in range(1,l) :

        if isPrime(int(s[:a])) == False or isPrime(int(s[a:])) == False :

            return False


    return True


num = 11
found = 0
sum = 0

while found < 11 :

    if truncatablePrime(num) == True :

        print num

        sum += num
        found += 1

    num += 2


print sum

