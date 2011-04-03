#! /usr/bin/python

dict = {
	1 : "one",
	2 : "two",
	3 : "three",
	4 : "four",
	5 : "five",
	6 : "six",
	7 : "seven",
	8 : "eight",
	9 : "nine",
	10 : "ten",
	11 : "eleven",
	12 : "twelve",
	13 : "thirteen",
	14 : "fourteen",
	15 : "fifteen",
	16 : "sixteen",
	17 : "seventeen",
	18 : "eighteen",
	19 : "nineteen",
	20 : "twenty",
	30 : "thirty",
	40 : "forty",
	50 : "fifty",
	60 : "sixty",
	70 : "seventy",
	80 : "eighty",
	90 : "ninety",
	100 : "hundred",
	1000 : "onethousand" }

charcount = 0
charcount += len(dict[1000])

# 1 to 999
for nr in range(1,1000) :
	hun = nr / 100
	ten = (nr-hun*100)/10
	last = (nr-hun*100-ten*10)

	word = ""

	if( hun > 0 ) :
		word += dict[hun]
		word += dict[100]

		if( ten > 0 or last > 0 ) :
			word += "and"

	if( ten == 1 ) :
		word += dict[ten*10+last]

		last = 0

	if( ten > 1 ) :
		word += dict[ten*10]
		
	if( last > 0 ) :
		word += dict[last]

	charcount += len(word)
		
	print "%d %d %d %d %s" % (nr,hun,ten,last,word)

print charcount

