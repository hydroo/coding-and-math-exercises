#! /usr/bin/python

fracs = []
searched = []

a = 10
while a < 100 :

	b = a+1
	while b < 100 :

		frac = float(a)/float(b)

		fracs.append([a,b])


		b = b + 1

	a = a + 1

for a in fracs :

	print a

print "----------"

for a in fracs :

	enum = str(a[0])
	denom = str(a[1])

	frac = float(enum) / float(denom)

	if enum[1] == denom[0] :

		newenum = float(enum[0])
		newdenom = float(denom[1])

#		print str(fracs[a])+" "+str(newenum)+"/"+str(newdenom)

		if newdenom != 0.0 :

			newfrac = newenum/newdenom
			
			if frac+0.0001 > newfrac and frac-0.0001 < newfrac:

				print "!!! "+str(a)
				searched.append(a)

	if enum[0] == denom[1] :

		newenum = float(enum[1])
		newdenom = float(denom[0])

#		print str(fracs[a])+" "+str(newenum)+"/"+str(newdenom)

		if newdenom != 0.0 :
			
			newfrac = newenum/newdenom

			if frac+0.0001 > newfrac and frac-0.0001 < newfrac :

				print "!!! "+str(a)
				searched.append(a)


enum = 1
denom = 1
for a in searched :

	enum = enum * a[0]
	denom = denom * a[1]

# safe - because I use enum/denom for ggT
enumm = enum
denomm = denom

print str(enum)+"/"+str(denom)

while enum > 0 :

	if denom > enum :
		a = denom
		denom = enum
		enum = a
	
	enum = enum % denom

	print str(enum)+" "+str(denom)

print "------"
print str(enumm / denom) + " " + str(denomm / denom)

