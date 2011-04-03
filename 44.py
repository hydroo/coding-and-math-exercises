#! /usr/bin/python

from math import *

def isPentagonal(n) :

    if ((sqrt(24*n+1)+1) / 6) % 1 == 0 :
        return True
    else :
        return False


def pentagon(n) :

    return n*(3*n-1) / 2

max = 100000
minimized = 10000000000000000000000000

a = 1
while a < max :

    print str(a)

    b = a
    while b < max :

        aa = pentagon(a)
        bb = pentagon(b)

        dd = bb-aa

        #print str(aa) + " " + str(bb)

        if isPentagonal(aa+bb) == True and isPentagonal(dd) == True :

            if dd < minimized :
                minimized = dd
                print str(minimized) + " a: " + str(aa) + " b: " + str(bb)

        b += 1
    
    a += 1


print minimized
