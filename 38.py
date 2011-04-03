#! /usr/bin/python

def isPandigital(s) :

    nrs = { '0' : True,
            '1' : False,
            '2' : False,
            '3' : False,
            '4' : False,
            '5' : False,
            '6' : False,
            '7' : False,
            '8' : False,
            '9' : False }

    for a in range(len(s)) :

        if nrs[s[a]] == False :
            nrs[s[a]] = True
        else :
            return False

    return True


for factors in range(2,100) :

    factor = 192
    result = ""

    while len(result) < 10 :

        result = ""

        for a in range(1,factors+1) :

            result += str(a*factor)


        if len(result) == 9 and isPandigital(result) :

            print str(factor) + "  " + str(factors) + "   " + result

        factor += 1


