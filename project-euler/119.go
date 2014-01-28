package main

import (
	"fmt"
	"math"
)


func digitSum(n int64) int64 {

	sum := int64(0)
	digitCount := int(math.Log10(float64(n))) + 1

	for digit := 0; digit < digitCount; digit += 1 {

		newN := n / 10

		sum += n - ((newN)*10)

		n = newN

	}

	return sum
}

func main() {

	nMax := int64(100)
	expMax := int64(10)

	for n := int64(2); n <= nMax; n += 1 {

		number := n

		for exp := int64(1); exp <= expMax; exp += 1 {

			if number < 0 {
				panic(fmt.Sprint(n, exp, number))
			}

			if number > 9 && digitSum(number) == n {
				fmt.Printf("%.20d\n",number)
			}

			number *= n

		}

	}
}

