#! /usr/bin/python


from math import *

def isTriangleNumber(n) :

    x1 = -0.5 + sqrt(0.25 + 2*n)
    x2 = -0.5 - sqrt(0.25 + 2*n)

    if x1 % 1 == 0 or x2 % 1 == 0 :

        return True

    else :

        return False


alphabet = { 'a' : 1,
             'b' : 2,
             'c' : 3,
             'd' : 4,
             'e' : 5,
             'f' : 6,
             'g' : 7,
             'h' : 8,
             'i' : 9,
             'j' : 10,
             'k' : 11,
             'l' : 12,
             'm' : 13,
             'n' : 14,
             'o' : 15,
             'p' : 16,
             'q' : 17,
             'r' : 18,
             's' : 19,
             't' : 20,
             'u' : 21,
             'v' : 22,
             'w' : 23,
             'x' : 24,
             'y' : 25,
             'z' : 26,
             '\"' : 0 }


s = ""

f = file("42_input.txt")
for line in f.readlines() :
    s += line

s = s.lower()

words = s.split(',')

howmany = 0

for word in words :

    n = 0

    for i in range(len(word)) :
        n += alphabet[word[i]]

    if isTriangleNumber(n) :
        howmany += 1

print howmany

