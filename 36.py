#! /usr/bin/python


def dec2bin(n) :

	bin = ""

	while n > 0 :

		if n % 2 == 0 :
			bin += "0"
			n = n / 2
		else :
			bin += "1"
			n = (n-1) / 2

	return bin

def palindrom(s,a,e) :

	if a >= e :
		return True
	else :
		return s[a] == s[e] and palindrom(s,a+1,e-1)


sum = 0

dec = 1
while dec < 1000000 :

	bin = dec2bin(dec)

	sdec = str(dec)
	sbin = str(bin)

	if palindrom(sdec,0,len(sdec)-1) and palindrom(sbin,0,len(sbin)-1) :

		sum += dec

		print sdec+"  "+sbin







	dec = dec + 2

print "sum of all palindroms: "+str(sum)


