#! /usr/bin/python

from fraction import *


sqrts = {}
a = 2
while a < 1000 :

    sqrts[a**2] = 1

    a += 1



a = 2
max = 10000
sum = 0


while a <= max :


    if sqrts.has_key(a) :
        a += 1
        continue

    if a % 1000 == 0 :
        print "a: " + str(a)


    periodfound = False
    s = [(sqrt(float(a)), 0, sqrt(float(a) - (sqrt(float(a)) % 0.0000000001)))]

    s2 = {(s[-1][2], 0) : 1}



    b = 0
    while not periodfound and b < 1000000 :

        f = float(s[-1][0])
        i = int(f)

        res = 1.0 / (f-i)
        rest = res % 0.0000000001

        s.append((res,i,res-rest))

        if s2.has_key((s[-1][0]- rest,i)) :


            j = 1
            while j < len(s) :

                if s[j][1] == i and s[j][2] == (s[-1][0]- rest) :


                    if len(s[j:-1]) % 2 != 0 :
                        sum += 1
                        print "o  " + str(a) + "  " + str(len(s[j:-1])) + "  " + str(sum)
                    else :
                        print "e  " + str(a) + "  " + str(len(s[j:-1]))

                    break

                j += 1



            #print "!!!!!!!!!!!!!!!!!!!!!!!!!!!"
            break

        #print str(i) + "\t" + str(s[-1])

        s2[(s[-1][2],i)] = 1

        b += 1


    # do stuff

    a += 1


print "sum of odd numbers with an odd period: " + str(sum)

