#! /usr/bin/python

def letterStats(letters) :

    stats = {}

    for letter in letters :

        if not stats.has_key(letter) :
            stats[letter] = 0

        stats[letter] += 1


    for letter in stats.keys() :

        print str(letter) + " = " + str(stats[letter])

letters = []
cipher = ""

f = file("59_cipher1.txt")
for line in f.readlines() :
    for letter in line.split(",") :
        letters.append(letter)
    letters[-1] = letters[-1].rstrip("\r\n")

for letter in letters :
    cipher += chr(int(letter))


password = [ord("g"),ord("o"),ord("d")]


#print letters

#for a in range(len(password)) :

#    print str(a) + " {"
#    letterStats(letters[a::len(password)])
#    print "}"


letters2 = []
sum = 0
i = 0
for letter in letters :
    i = i % 3

    letters2.append(int(letter)^password[i])
    sum += letters2[-1]

    i += 1

decipher = ""
i = 0
for letter in letters2 :
    i = i % 3

    #if i == 0 :
    #    decipher += " "

    decipher += chr(int(letter))

    i += 1

print decipher
print sum

