#! /usr/bin/python

sum = 1

for a in range(201) :

	for b in range(101) :
		bb = a + b*2
		if bb > 200 :
			break

		for c in range(41) :
			cc = bb + c*5
			if cc > 200 :
				break

			for d in range(21) :
				dd = cc + d*10
				if dd > 200 :
					break

				for e in range(11) :
					ee = dd + e*20
					if ee > 200 :
						break

					for f in range(5) :
						ff = ee + f*50
						if ff > 200 :
							break

						for g in range(3) :
							gg = ff + g*100
							if gg == 200 :
								sum = sum + 1
	print a,sum

print sum

