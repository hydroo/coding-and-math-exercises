#! /usr/bin/python

from math import *

def triangle(n) :

    return n*(n+1) / 2

def reversePentagonal(n) :

    return (sqrt(24*n+1)+1) / 6

def reverseHexagonal(n) :

    return (sqrt(8*n + 1) + 1) / 4

max = 100000
Nt = 1
while Nt < 100000 :

    T = triangle(Nt)
    Np = reversePentagonal(T)

    if Np % 1 == 0 :

        Nh = reverseHexagonal(T)

        if Nh % 1 == 0 :

            print str(T) + " !!!!!!!!!!!"

    Nt += 1

