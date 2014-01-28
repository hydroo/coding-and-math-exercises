#! /usr/bin/python

from math import *

def haveSameDigits(s1,s2) :

    digits = {}

    for c1 in s1 :
        digits[c1] = 1

    for c2 in s2 :
        if digits.has_key(c2) == False :
            return False
        else :
            digits[c2] = 2

    for nr in digits.values() :
        if nr == 1 :
            return False

    return True

a = 1
max = 1000000000000
while a < max :

    if a % 1000000 == 0:
        print a

    if haveSameDigits(str(a),str(a*2)) and haveSameDigits(str(a),str(a*3)) and haveSameDigits(str(a),str(a*4)) and haveSameDigits(str(a),str(a*5)) and haveSameDigits(str(a),str(a*6)) :

        print str(a) + "!!!!!!!!!!!!!!!"



    a += 1
