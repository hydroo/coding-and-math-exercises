#! /usr/bin/python

from math import *


def palindrom(s,a,e) :

    if a >= e :
        return True
    else :
        return s[a] == s[e] and palindrom(s,a+1,e-1)

def isPalindrom(s) :
    return palindrom(s,0,len(s)-1)

def reverse(n) :
    return int(str(n)[::-1])



a = 0
max = 10000

sum = 0

while a <= max :

    n = a

    i = 0
    while i < 50 :

        n = n + reverse(n)

        if isPalindrom(str(n)) :
            break

        i += 1

    if i == 50 :
        print a
        sum += 1

    a += 1

print str(sum) + " lychrel numbers are below " + str(max)

