#! /usr/bin/python

def checksum(n) :
    s = str(n)

    ret = 0

    for c in s :
        ret += int(c)

    return ret

maxchecksum = 0

a = 0
maxa = 99

while a <= 99 :

    exp = 0
    maxexp = 99
    while exp <= 99 :

        n = checksum(a**exp)

        if n > maxchecksum :
            maxchecksum = n
            print n

        exp += 1

    a += 1


print maxchecksum



