#! /usr/bin/python

from math import *

def isPandigital(s,nrs) :

    for i in range(len(s)) :
        if nrs[s[i]] == False :
            nrs[s[i]] = True
        else :
            return False

    return True


def isPrime(num) :

    if num < 2 :
        return False

    for i in range(2,int(sqrt(num))+1) :
        if num % i == 0 :
            return False

    return True



biggestpandigitalevarrrr = 0


for pan in range(8,1,-1) :

    dict = { '0' : True,
            '1' : True,
            '2' : True,
            '3' : True,
            '4' : True,
            '5' : True,
            '6' : True,
            '7' : True,
            '8' : True,
            '9' : True }


    smallest = ""
    biggest = ""

    for a in range(1,pan+1) :
        dict[str(a)] = False
        smallest += str(a)
        biggest += str(pan+1-a)


    smallestnr = int(smallest)
    a = int(biggest)

    print biggest + " >> " + smallest

    while a >= smallestnr :

        if a % 500000 < 2 :
            print "  " + str(a)

        if isPandigital(str(a),dict.copy())  == True :

            if isPrime(a) == True and biggestpandigitalevarrrr < a :
                biggestpandigitalevarrrr = a
                print ">>>>>>>>>>>>>" + str(biggestpandigitalevarrrr) + "<<<<<<<<<<<<<<<<<<<<<<"


        a -= 2


print str(biggestpandigitalevarrrr) + " !!!"

