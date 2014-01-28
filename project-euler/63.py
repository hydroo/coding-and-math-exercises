#! /usr/bin/python

nrs = {}

base = 1
while base < 1000 :

    exp = 1
    while exp < 200 :

        nr = base**exp

        if exp == len(str(nr)) :
            nrs[nr] = 1

        exp += 1

    base += 1

print len(nrs)

