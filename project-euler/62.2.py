#! /usr/bin/python

from math import *
from copy import *

def analyze(s) :

    ret = [0,0,0,0,0, 0,0,0,0,0]

    for c in s :
        ret[int(c)] += 1

    return ( (ret[1],ret[2],ret[3],ret[4] , ret[5],ret[6],ret[7],ret[8],ret[9]),ret[0])


cubes = {}


a = 1
max = 1000001
while a < max :

    cube = a**3

    digits = analyze(str(cube))

    #print str(cube) + str(digits)

    if not cubes.has_key(digits[0]) :
        cubes[digits[0]] = []
    cubes[digits[0]].append((digits[1],cube))


    a += 1



smallestnumber = -1
smallestnumber2 = -1
for digits in cubes.keys() :

    if len(cubes[digits]) >= 5 :

        if len(cubes[digits]) > 5 and cubes[digits][4][0] == cubes[digits][5][0] :
            continue

        samelen = False
        if cubes[digits][0][0] == cubes[digits][1][0] and \
                cubes[digits][1][0] == cubes[digits][2][0] and \
                cubes[digits][2][0] == cubes[digits][3][0] and \
                cubes[digits][3][0] == cubes[digits][4][0] :
            samelen = True

        zeros = cubes[digits][4][0]

        if samelen == True :
            for tuple in cubes[digits] :
                if tuple[0] == zeros and (smallestnumber2 > tuple[1] or smallestnumber2 == -1) :
                    smallestnumber2 = tuple[1]
                    print str(smallestnumber2) + "  " + str(cubes[digits])
                    #print str(smallestnumber2) + "  " + str(zeros)
        else :
            for tuple in cubes[digits] :
                if tuple[0] == zeros and (smallestnumber > tuple[1] or smallestnumber == -1) :
                    smallestnumber = tuple[1]
                    print str(smallestnumber) + "  " + str(cubes[digits])
                    #print str(smallestnumber) + "  " + str(zeros)
        #print cubes[digits]
        #print "  " + str(len(str(cubes[digits][-1][1])))

print smallestnumber
print smallestnumber2
#print cubes

