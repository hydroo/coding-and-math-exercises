#! /usr/bin/python


# this is not totally right ... the second result is the wanted result

from math import *


def isPrime(num) :

    if num < 2 :
        return False

    for i in range(2,int(sqrt(num))+1) :
        if num % i == 0 :
            return False

    return True

max = 1000000000000000
a = 3
while a < max :

    if isPrime(a) :

        s = str(a)

        for pos in range(len(s)) :

            nrofprimes = 0

            for digit in ["0","1","2","3","4","5","6","7","8","9"] :

                if isPrime(int(s.replace(s[pos],digit))) == True :

                    nrofprimes += 1


            if nrofprimes == 8 :
                print s + "!!!!!!!!!!!!!"


    a += 2
    
