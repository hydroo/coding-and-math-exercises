#! /usr/bin/python


from math import *



def isPrime(num) :

    if num < 2 :
        return False

    for i in range(2,int(sqrt(num))+1) :
        if num % i == 0 :
            return False

    return True


def isPrime2(n) :

    if isPrime(n) :
        return 1
    else :
        return 0

tl = [5]
tr = [3]
br = [9]
bl = [7]


a = 3
max = 10000000
nprimes = 3
while a < max :

    tl.append(tl[-1]+a-1+a+a+a+1)
    tr.append(tr[-1]+a-1+a-1+a+a)
    br.append(br[-1]+1+a+a+1+a+1+a+1)
    bl.append(bl[-1]+a+a+a+1+a+1)


    nprimes += isPrime2(tl[-1])
    nprimes += isPrime2(tr[-1])
    nprimes += isPrime2(br[-1])
    nprimes += isPrime2(bl[-1])


    ratio = float(nprimes) / float(len(tl)*4)

    print ratio

    if ratio < 0.1 :

        print a
        break


    a += 2

#print tl
#print tr
#print br
#print bl

