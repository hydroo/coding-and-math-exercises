#! /usr/bin/python

def isPandigital(s) :

    nrs = { '0' : False,
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


sum = 0


n0 = 0
while n0 < 10 :

    s0 = str(n0)

    n1 = 10
    while n1 < 1000 :

        s1 = str(n1)
        if len(s1) == 2 :
            s1 = "0" + s1
        
        n2 = 14
        while n2 < 1000 :

            s2 = str(n2)
            if len(s2) == 2 :
                s2 = "0" + s2

            n3 = 17
            while n3 < 1000 :

                s3 = str(n3)
                if len(s3) == 2 :
                    s3 = "0" + s3

                s = s0 + s1 + s2 + s3

                if isPandigital(s) == True :

                    if int(s[2:5]) % 3 == 0 and int(s[3:6]) % 5 == 0 and int(s[5:8]) % 11 == 0 and int(s[6:9]) % 13 == 0 :

                        print s

                        sum += int(s)


                n3 += 17

            n2 += 7

        n1 += 2
    
    n0 += 1

print "sum = " + str(sum)

