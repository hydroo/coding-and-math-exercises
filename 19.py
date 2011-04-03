#! /usr/bin/python

weekdays = {
	0 : "Monday",
	1 : "Tuesday",
	2 : "Wednesday",
	3 : "Thursday",
	4 : "Friday",
	5 : "Saturday",
	6 : "Sunday",
}

start = ( 0, 0, 1901 )
end = ( 30, 11, 2000 )

dayspermonth = {
		0 : 31,
		1 : 28,
		2 : 31,
		3 : 30,
		4 : 31,
		5 : 30,
		6 : 31,
		7 : 31,
		8 : 30,
		9 : 31,
		10 : 30,
		11 : 31
}

day = 365 % 7
count = 0

for year in range(start[2],end[2]+1) :

	leapyear = False

	if year % 4 == 0 :
		leapyear = True
	if year % 100 == 0 :
		leapyear = False
	if year % 400 == 0 :
		leapyear = True


	if leapyear == True :
		dayspermonth[1] = 29
	else :
		dayspermonth[1] = 28

	for month in dayspermonth :

		if day == 6 :
			count = count + 1

		day += dayspermonth[month]
		day %= 7

		print "year: %d leap: %d month: %d firstday: %d count: %d" % (year,leapyear,month,day,count)

	


