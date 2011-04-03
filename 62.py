#! /usr/bin/python

from copy import *


def permutations(scur, srest) :

    if srest == "" :
        return {scur : 1}

    ret = {}

    for c in srest :
        snewrest = copy(srest)
        snewrest = snewrest[:snewrest.find(c)] + snewrest[snewrest.find(c)+1:]

        for permut in permutations(scur + c,snewrest) :
            ret[permut] = 1

    return ret


cubes = {}
cubesl = []

a = 300
max = 1000000
while a < max :
    cubes[a**3] = 1
    cubesl.append(a**3)
    a += 1

a = 0
for cube in cubesl :

    #if cube < 1051871913 :
    #    continue

    foundcubes = {}

    for permut in permutations("",str(cube)).keys() :
        if cubes.has_key(int(permut)) and not foundcubes.has_key(int(permut)):
            foundcubes[int(permut)] = 1


    if len(foundcubes) == 5 :
        print " >>>>>>>> " + str(cube) + "  " + str(len(foundcubes))  + "  " + str(foundcubes) + "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"

    a = a % 10

    if a == 0 :
        print str(cube) + "  " + str(len(foundcubes)) + "  " + str(foundcubes)

    a += 1


