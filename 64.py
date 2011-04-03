#! /usr/bin/python

from fraction import *


def asdf(den_sqrt,den_add,num) :

    r_add = 0
    r_den_sqrt = 0.0
    r_den_add = 0
    r_num = 0


    r_add = int(num / (sqrt(den_sqrt)+den_add))

    r_den_sqrt = den_sqrt
    r_num = (den_sqrt + (den_add*(den_add*-1)) ) / num
    r_den_add = (den_add*-1) - r_num*r_add

    return (r_add, (r_den_sqrt, r_den_add, r_num) )






nr = 2
max = 10000
sum = 0


while nr <= max :

    if nr % 1000 == 0 :
        print "a: " + str(nr)

    if sqrt(float(nr)) % 1 == 0 :
        nr += 1
        continue


    foundperiod = False

    # result to index mapping
    d = {}
    res = (int(sqrt(nr)),(nr,int(sqrt(nr))*-1,1))
    i = 0
    periodlength = 0

    while not foundperiod :

        d[res] = i

        res = asdf(res[1][0],res[1][1],res[1][2],)

        if d.has_key(res) :
            foundperiod = True
            periodlength = i - d[(res)] + 1


        i += 1

    assert foundperiod

    if periodlength % 2 != 0 :
        sum += 1

    print str(nr) + "\t" + str(periodlength)


    nr += 1




print "sum of odd numbers with an odd period: " + str(sum)

