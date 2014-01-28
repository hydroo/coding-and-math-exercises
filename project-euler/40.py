#! /usr/bin/python

nr = 1
s = ""
a = 0

while nr < 1000000 :

    s += str(nr)

    nr += 1



print str(int(s[1 - 1]) * int(s[10 - 1]) * int(s[100 - 1]) * int(s[1000 - 1]) * int(s[10000 - 1]) * int(s[100000 - 1]) * int(s[1000000 - 1]))

