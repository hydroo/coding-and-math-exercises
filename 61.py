#! /usr/bin/python


from copy import *


numbers = {
    3 : [],
    4 : [],
    5 : [],
    6 : [],
    7 : [],
    8 : [],
    }

numbers2 = {}

def triangles() :
    i = 1
    while (i*(i+1)/2) < 10000 :
        if (i*(i+1)/2) > 999 :
            numbers[3].append(i*(i+1)/2)
            numbers2[i*(i+1)/2] = 3
        i += 1
    return

def squares() :
    i = 1
    while (i*i) < 10000 :
        if (i*i) > 999 :
            numbers[4].append(i*i)
            numbers2[i*i] = 4
        i += 1
    return

def pentagonals() :
    i = 1
    while (i*(3*i-1)/2) < 10000 :
        if (i*(3*i-1)/2) > 999 :
            numbers[5].append(i*(3*i-1)/2)
            numbers2[i*(3*i-1)/2] = 5
        i += 1
    return

def hexagonals() :
    i = 1
    while (i*(2*i-1)) < 10000 :
        if (i*(2*i-1)) > 999 :
            numbers[6].append(i*(2*i-1))
            numbers2[i*(2*i-1)] = 6
        i += 1
    return

def heptagonals() :
    i = 1
    while (i*(5*i-3)/2) < 10000 :
        if (i*(5*i-3)/2) > 999 :
            numbers[7].append(i*(5*i-3)/2)
            numbers2[i*(5*i-3)/2] = 7
        i += 1
    return

def octagonals() :
    i = 1
    while (i*(3*i-2)) < 10000 :
        if (i*(3*i-2)) > 999 :
            numbers[8].append(i*(3*i-2))
            numbers2[i*(3*i-2)] = 8
        i += 1
    return


triangles()
squares()
pentagonals()
hexagonals()
heptagonals()
octagonals()


def numbers2contains(s) :

    min = int(s + "00")
    max = int(s + "99")

    ret = []

    for number in numbers2 :
        if number >= min and number <= max :
            ret.append(number)

    return ret


#print numbers2

def extendRow(list,fig) :

    if len(list) > 5 :
        return

    l = copy(list)
    f = copy(fig)

    f[numbers2[l[-1]]] = 1


    s34 = str(l[-1])[-2:]
    matches = numbers2contains(s34)

    for match in matches :
        index = -1
        try :
            index = l.index(match)
        except:
            pass

        if f.has_key(numbers2[match]) == False and index == -1:
            extendRow(l + [match], f)



            if len(l) == 5 and str(l[0])[:2] == str(match)[-2:] :
                print str(l + [match]) + str(f) + "!!!!!!!!"
    return



for n in numbers2.keys() :

    extendRow([n],{})

