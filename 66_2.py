#! /usr/bin/python

from math import *

d = 62.0
dmax = 100.0
largestx = 1

while d <= dmax :

    if int(sqrt(d)) == sqrt(float(d)) :
        d += 1
        continue

    x = 2

    found = False
    while not found :

        y = sqrt(((x**2) - 1)/d)

        # print str(d) + "  " + str(num) + "  "  + str(den) + "  " + str(res)

        if y % 1 == 0 :
            print "d " + str(d) + "\t x " + str(x) + "\t y " + str(y)
            found = True
            break
        else :
            print x
            x += 1

    d += 1

