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
                self.den = 1
            else :
                self.den = d
        else :
            assert 0

    def __str__(self) :
        return str(self.num) + "/" + str(self.den)
    
    def __repr__(self) :
        return repr(self.num) + "/" + repr(self.den)

    def __int__(self) :
        return int(self.num / self.den)
    def __long__(self) :
        return long(self.num / self.den)
    def __float__(self) :
        return float(self.num) / float(self.den)

    def __abs__(self) :
        if self < 0 :
            return self*-1
        else :
            return self

    def __add__(self,n) :
        if isinstance(n,(int, long)) :
            n = Fraction(n)

        lecomu = lcm(self.den,n.den)

        return Fraction(self.num*(lecomu/self.den) + n.num*(lecomu/n.den), lecomu)

    def __sub__(self,n) :
        return self+(n*-1)

    def __mul__(self,n) :
        if isinstance(n,(int, long)) :
            n = Fraction(n,1)

        return Fraction(self.num*n.num,self.den*n.den)

    def __div__(self,n) :
        if isinstance(n,(int, long)) :
            n = Fraction(n,1)

        return Fraction(self.num*n.den,self.den*n.num)

    def __mod__(self,n) :
        if isinstance(n,(int, long)) :
            n = Fraction(n,1)

        lecomu = lcm(self.den,n.den)

        self2 = Fraction(self.num*(lecomu/self.den),lecomu)
        n2 = Fraction(n.num*(lecomu/n.den), lecomu)

        return Fraction(self2.num % n2.num,lecomu)

    def __pow__(self,n) :
        if isinstance(n,(int, long)) :
            n = Fraction(n,1)

        f = float(n)
        i = long(n)

        if f % 1.0 != 0.0 :
            return float((self.num**f) / (self.den**f))
        else :
            return Fraction(self.num**i, self.den**i)

    def __radd__(self, n) :
        return self + n
    def __rsub__(self, n) :
        if isinstance(n,(int, long)) :
            n = Fraction(n,1)
        return n - self
    def __rmul__(self, n) :
        return self * n
    def __rdiv__(self, n) :
        if isinstance(n,(int, long)) :
            n = Fraction(n,1)
        return n / self
    def __rpow__(self, n) :
        if isinstance(n,(int, long)) :
            n = Fraction(n,1)
        return n**self

    # not needed - automagically defined
    # __iadd__(self, n) :
    # __isub__(self, n) :
    # __imul__(self, n) :
    # __idiv__(self, n) :
    # __imod__(self, n) :
    # __ipow__(self, n) :

    def __lt__(self, n) :
        if isinstance(n,(int, long)) :
            n = Fraction(n,1)
        lecomu = lcm(self.den,n.den)

        self2 = Fraction(self.num*(lecomu/self.den),lecomu)
        n2 = Fraction(n.num*(lecomu/n.den), lecomu)

        if lecomu < 0 :
            ret = self2.num > n2.num
        else :
            ret = self2.num < n2.num

        return ret

    def  __le__(self, n) :
        return self < n or self == n
    def __eq__(self, n) :
        if isinstance(n,(int, long)) :
            n = Fraction(n,1)
        sr = self.reduce()
        nr = n.reduce()
        return sr.num == nr.num and sr.den == nr.den
    def __ne__(self, n) :
        return not self == n
    def __gt__(self, n) :
        if isinstance(n,(int, long)) :
            n = Fraction(n,1)
        lecomu = lcm(self.den,n.den)

        self2 = Fraction(self.num*(lecomu/self.den),lecomu)
        n2 = Fraction(n.num*(lecomu/n.den), lecomu)

        if lecomu < 0 :
            ret = self2.num < n2.num
        else :
            ret = self2.num > n2.num

        return ret

    def  __ge__(self, n) :
        return self > n or self == n

    def reciprocal(self) :
        return Fraction(self.den,self.num)

    def reduce(self) :
        grcodi = gcd(self.num,self.den)
        return Fraction(self.num/grcodi,self.den/grcodi)

