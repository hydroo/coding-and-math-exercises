#! /usr/bin/python

longestpattern = 0
longestpatternid = 0
longestpatternstr = ""

for d in range(1,1001) :

	rest = 1

	frac = "0."

	rests = {}

	while True :

		rest = rest * 1000

		newrest = rest % d

		add = str((rest - newrest) / d)

		while len(add) < 3 :
			add = "0"+add

		frac = frac + add

		rest = newrest

		if rest == 0 :
			break

		if rests.has_key(rest) :
			if longestpattern < rests[rest] :
				longestpattern = rests[rest]
				longestpatternid = d
				longestpatternstr = frac
				print longestpatternid,longestpattern,add,longestpatternstr
			break

		rests[rest] = 0

		for a in rests.keys():
			rests[a] = rests[a] + 1

