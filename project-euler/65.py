#! /usr/bin/python

from fraction import *


#print "%d, %s, %f" % (0, "asdf", 0.0)


E = [2,1,2,]

a = 4
while len(E) < 100 :

    E.append(1)
    E.append(1)
    E.append(a)

    a += 2

# len = 100
E = E[0:100]


def makeFrac(E, i) :

    if i == 99 :

        return Fraction(E[i],1)
        
    else :
        return E[i] + (1 / makeFrac(E,i+1))


sum = 0
s = str(makeFrac(E,0).num)
for c in s :
    sum += int(c)
print sum

