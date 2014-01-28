#! /usr/bin/python

from math import *


def gcd(n,m) :
    if n < m :
        t = n
        n = m
        m = t

    while m != 0 and (n % m) < n :
        n = n % m

        if n < m :
            t = n
            n = m
            m = t

    return n

def lcm(n,m) :
    return abs(n*m) / gcd(n,m)


class Fraction :

    def __init__(self,n = None,d = None) :
        if n is None :
            self.num = 1
            self.den = 1
        if isinstance(n,Fraction) :
            self.num = n.num
            self.den = n.den
        elif isinstance(n,(int, long)) :
            self.num = n
            if d is None :
                self.den = n
            else :
                self.den = d

    def __str__(self) :
        return str(self.num) + "/" + str(self.den)
    
    def __repr__(self) :
        return repr(self.num) + "/" + repr(self.den)

    def reciprocal(self) :
        return Fraction(self.den,self.num)

    def __add__(self,n) :
        if isinstance(n,(int, long)) :
            n = Fraction(n)

        lecomu = lcm(self.den,n.den)

        return Fraction(self.num*(lecomu/self.den) + n.num*(lecomu/n.den), lecomu)

    def __mul__(self,n) :
        if isinstance(n,(int, long)) :
            n = Fraction(n,1)

        return Fraction(self.num*n.num,self.den*n.den)

    def __div__(self,n) :
        if isinstance(n,(int, long)) :
            n = Fraction(n,1)

        return Fraction(self.num*n.den,self.den*n.num)

    def reduce(self) :
        grcodi = gcd(self.num,self.den)
        return Fraction(self.num/grcodi,self.den/grcodi)


a = 0
max = 999
sum = 0

stack = [Fraction(3,2)]

while a < max :

    stack.append(((stack[-1]+2).reciprocal() + 1).reduce())

    a += 1

for entry in stack :

    if len(str(entry.num)) > len(str(entry.den)) :
        sum += 1

print sum

