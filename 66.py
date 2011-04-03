#! /usr/bin/python

from math import *

d = 2
dmax = 20
largestx = 1

while d <= dmax :

    if int(sqrt(d)) == sqrt(float(d)) :
        d += 1
        continue


    sqrtd = sqrt(float(d))
    
    num = int(sqrtd)
    den = 1

    found = False
    while not found :

        res = num**2 + - d*(den**2) 

        # print str(d) + "  " + str(num) + "  "  + str(den) + "  " + str(res)

        if res == 1 :
            print str(d) + "\t" + str(num) + "\t" + str(den)
            found = True
            break
        else :
            if sqrtd < ( float(num) / float(den) ) :
                den += 1
            else :
                num += 1
        # elif res < 1 :
        #     num += 1
        # else :
        #     den += 1

    d += 1

