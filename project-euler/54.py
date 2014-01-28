#! /usr/bin/python


val = {"2" : 2, "3" : 3, "4" : 4, "5" : 5, "6" : 6, "7" : 7, "8" : 8, "9" : 9, "T" : 10, "J" : 11, "Q" : 12, "K" : 13, "A" : 14 }


def findSmallestCard(v) :
    ret = v[0]
    for c in v :
        if val[ret[0]] > val[c[0]] :
            ret = c
    return ret

def findHighestCard(v) :
    ret = v[0]
    for c in v :
        if val[ret[0]] < val[c[0]] :
            ret = c
    return ret

def removeFirstCard(v,c1) :
    for c in v :
        if c.find(c1) != -1 :
            v.remove(c)
            return

def takeHighestCard(v) :
    c = findHighestCard(v)
    removeFirstCard(v,c)
    return c

def takeSmallestCard(v) :
    c = findSmallestCard(v)
    removeFirstCard(v,c)
    return c

def next(s) :
    if s == "2" :
        return "3"
    elif s == "3" :
        return "4"
    elif s == "4" :
        return "5"
    elif s == "5" :
        return "6"
    elif s == "6" :
        return "7"
    elif s == "7" :
        return "8"
    elif s == "8" :
        return "9"
    elif s == "9" :
        return "T"
    elif s == "T" :
        return "J"
    elif s == "J" :
        return "Q"
    elif s == "Q" :
        return "K"
    elif s == "K" :
        return "A"
    elif s == "A" :
        return ""

def prev(s) :
    if s == "2" :
        return ""
    elif s == "3" :
        return "2"
    elif s == "4" :
        return "3"
    elif s == "5" :
        return "4"
    elif s == "6" :
        return "5"
    elif s == "7" :
        return "6"
    elif s == "8" :
        return "7"
    elif s == "9" :
        return "8"
    elif s == "T" :
        return "9"
    elif s == "J" :
        return "T"
    elif s == "Q" :
        return "J"
    elif s == "K" :
        return "Q"
    elif s == "A" :
        return "K"

def isFlush(v) :
    if len(v) != 5 :
        return False

    color = v[0][1]
    for a in v :
        if a[1] != color :
            return False
    return True

def isStreet(v) :
    if len(v) != 5 :
        return False

    start = findSmallestCard(v)[0]
    needed = {}
    needed[start] = 0
    needed[next(start)] = 0
    needed[next(next(start))] = 0
    needed[next(next(next(start)))] = 0
    needed[next(next(next(next(start))))] = 0

    for c in v :
       if needed.has_key(c[0]) == False:
           return False
       else :
           needed[c[0]] = 1

    for a in needed.values() :
       if a == 0 :
           return False

    return True


def hasN(v,n) :
    if len(v) < n :
        return ""

    cards = {}

    for c in v :
        if cards.has_key(c[0]) == False :
            cards[c[0]] = 1
        else :
            cards[c[0]] += 1

    for a in cards.keys() :
        if cards[a] == n :
            i = 0
            while i < len(v) :
                if v[i][0] == a :
                    v.remove(v[i])
                    i -= 1
                i += 1
            return a

    return ""

def isFullHouse(v) :

    v2 = []
    for c in v :
        v2.append(c)

    if len(v2) != 5 :
        return ""

    s1 = hasN(v2,3)

    if s1 != "" :
        s2 = hasN(v2,2)
        if s2 != "" :
            v = []
            return s1 + s2
        else :
            return ""
    else :
        return ""

mul = {
        "straightflush" : 42, #21
        "four" : 40, #20
        "fullhouse" : 36, #18-19
        "flush" : 26, #13-17
        "straight" : 16, #8-12
        "three" : 14, #7
        "two" : 10, #5-6
        "high" : 0 #0-4
        }


def eval(v) :

    #print v

    v2 = []
    for c in v :
        v2.append(c)


    ret = 0

    if isFlush(v) and isStreet(v) :
        # straight flush/royal flush
        # print "straight flush  " + str(v2)
        c = takeSmallestCard(v)
        ret += (10**( mul["straightflush"] + 0 )) * val[c[0]]
        c = takeSmallestCard(v)
        ret += (10**( mul["straightflush"] + 2 )) * val[c[0]]
        c = takeSmallestCard(v)
        ret += (10**( mul["straightflush"] + 4 )) * val[c[0]]
        c = takeSmallestCard(v)
        ret += (10**( mul["straightflush"] + 6 )) * val[c[0]]
        c = takeSmallestCard(v)
        ret += (10**( mul["straightflush"] + 8 )) * val[c[0]]

        v = []

    four = hasN(v,4)
    if four != "" :
        # four of a kind
        # print "four of a kind  " + str(v2)
        ret += (10**( mul["four"] + 0 )) * val[four]

    fullhouse = isFullHouse(v)
    if fullhouse != "" :
        # print "full house  " + str(v2)
        # full house
        ret += (10**( mul["fullhouse"] + 0 )) * val[fullhouse[1]]
        ret += (10**( mul["fullhouse"] + 2 )) * val[fullhouse[0]]

        v = []

    if isFlush(v) :
        #flush
        # print "flush  " + str(v2)
        c = takeSmallestCard(v)
        ret += (10**( mul["flush"] + 0 )) * val[c[0]]
        c = takeSmallestCard(v)
        ret += (10**( mul["flush"] + 2 )) * val[c[0]]
        c = takeSmallestCard(v)
        ret += (10**( mul["flush"] + 4 )) * val[c[0]]
        c = takeSmallestCard(v)
        ret += (10**( mul["flush"] + 6 )) * val[c[0]]
        c = takeSmallestCard(v)
        ret += (10**( mul["flush"] + 8 )) * val[c[0]]

        v = []

    if isStreet(v) :
        #straight
        # print "straight  " + str(v2)
        c = takeSmallestCard(v)
        ret += (10**( mul["straight"] + 0 )) * val[c[0]]
        c = takeSmallestCard(v)
        ret += (10**( mul["straight"] + 2 )) * val[c[0]]
        c = takeSmallestCard(v)
        ret += (10**( mul["straight"] + 4 )) * val[c[0]]
        c = takeSmallestCard(v)
        ret += (10**( mul["straight"] + 6 )) * val[c[0]]
        c = takeSmallestCard(v)
        ret += (10**( mul["straight"] + 8 )) * val[c[0]]

        v = []

    three = hasN(v,3)
    if three != "" :
        # print "three of a kind" + str(three) + "  " + str(v2)
        ret += (10**( mul["three"] + 0 )) * val[three]

    two1 = hasN(v,2)
    two2 = hasN(v,2)

    if two2 != "" :
        # print "two pairs  " + two1 + "  " + two2 + "  " + str(v2)
        if val[two1] > val[two2] :
            ret += (10**( mul["two"] + 2 )) * val[two1]
            ret += (10**( mul["two"] + 0 )) * val[two2]
        else :
            ret += (10**( mul["two"] + 2 )) * val[two2]
            ret += (10**( mul["two"] + 0 )) * val[two1]
    elif two1 != "" :
        # print "one pair  " + two1 + "  " + str(v2)
        ret += (10**( mul["two"] + 0 )) * val[two1]

    add = 0
    while len(v) > 0 :
        # print "high  " + c
        c = takeSmallestCard(v)
        ret += (10**( mul["high"] + add )) * val[c[0]]
        add += 2


#-    * High Card: Highest value card.
#-    * One Pair: Two cards of the same value.
#-    * Two Pairs: Two different pairs.
#-    * Three of a Kind: Three cards of the same value.
#-    * Straight: All cards are consecutive values.
#-    * Flush: All cards of the same suit.
#-    * Full House: Three of a kind and a pair.
#-    * Four of a Kind: Four cards of the same value.
#-    * Straight Flush: All cards are consecutive values of same suit.
#-    * Royal Flush: Ten, Jack, Queen, King, Ace, in same suit.

#    print "    = " + str(ret)

    return ret



# eval(["6A","6B","6C","7A","7B"])
# eval(["AA","KA","QA","JA","TA"])
# eval(["9A","KA","QA","JA","TA"])
# eval(["AB","KA","QA","JA","TA"])
# eval(["7A","7B","6C","6A","4B"])
# eval(["7A","9B","TC","2A","2B"])
# eval(["7A","9B","AC","3A","3B"])
# eval(["7A","7B","TC","TA","3B"])




cards = []

f = file("54_poker.txt")
for line in f.readlines() :
    cards.append(line.split(" "))
    cards[-1][-1] = cards[-1][-1].rstrip("\r\n")

win1 = 0
for tencards in cards :

    ret1 = eval(tencards[0:5])
    ret2 = eval(tencards[5:10])

    between = ""
    if ret1 > ret2 :
        between = " > "
    elif ret1 < ret2 :
        between = " < "
    else :
        assert False

    # print str(tencards[0:5]) + " vs " + str(tencards[5:10]) + "  --  " + str(ret1) + " (" + str(len(str(ret1)))+ ")" + between + str(ret2) + " (" + str(len(str(ret2)))+ ")"

    if  ret1 > ret2 :
        win1 += 1
        #print "1"
    else :
        #print "2"
        pass

print str(win1) + " vs " + str(len(cards)-win1)

