#! /usr/bin/python

from math import *


def hasUniqueDigits(s) :

    digits = {}

    for a in s :

        #print a

        if digits.has_key(a) == True :

            return False

        else :

            digits[a] = 1

    return True



def isPermutationOf(s1,s2) :

    for a in s1 :

        if s2.find(a) == -1 :

            return False

    for a in s2 :

        if s1.find(a) == -1 :

            return False


    return True



def isPrime(num) :

    if num < 2 :
        return False

    for i in range(2,int(sqrt(num))+1) :
        if num % i == 0 :
            return False

    return True





a1 = 1000
while a1 < 10000 :

 #   print a1

    if isPrime(a1) == True :



        add = 1
        while a1 + 2*add < 10000 :

            a2 = a1 + add
            a3 = a2 + add

            if isPrime(a2) and isPrime(a3) and isPermutationOf(str(a1),str(a2)) and isPermutationOf(str(a1),str(a3)) :

                print str(a1) + " " + str(a2) + " " + str(a3) + " - " + str(add)

            add += 1

    

    a1 += 1

