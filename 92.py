#! /usr/bin/env python3

n = 1
count = 0

while n < 10000000 :

    # print(n)

    result = n

    while result != 89 and result != 1 :

        # print("  ", result)

        strn = str(result)

        result = 0

        max = len(strn)
        i = 0
        while i < max :
            digit = int(strn[i])
            result += digit*digit

            i+=1
            


    if result == 89 :

        count+=1
        print(n, count)

    n+=1

