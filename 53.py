#! /usr/bin/python

def fak(n) :

    if n == 0 :
        return 1
    else :
        ret = 1
        i = n
        while i > 0 :
            ret *= i
            i -= 1
        return ret

def binKoeff(n,r) :

    return fak(n) / ( fak(r)*fak(n-r) )


sum = 0
a = 1
while a < 101 :

    print a

    b = 1
    while b <= a :

        if binKoeff(a,b) > 1000000 :

            sum += 1

        b += 1

    a += 1

print "sum " + str(sum)

