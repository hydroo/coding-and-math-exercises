package main

import (
	"fmt"
	"math"
)


func isPalindrom(n int) bool {

	s := fmt.Sprint(n)

	l := len(s)

	for i := 0; i < l; i += 1 {

		if s[i] != s[l-1-i] {
			return false
		}

	}

	return true

}


func isSumOfConsecutiveSquares(n int) bool {

	n2 := n

	end := int(math.Sqrt(float64(n)))

	n2 -= end*end

	start := end - 1

	for ;start >= 1 && end >= 2; {

		n2 -= start*start
		start -= 1

		for ;n2  < 0; {
			n2 += end*end
			end -= 1
		}
		
		if n2 == 0 {
			fmt.Println("  ", n , start, end)
			return true
		}

	}

	return false

}


func main() {

	min := 2
	max := 99999999

	sum := int64(0)

	for n := min; n <= max; n += 1 {

		if isPalindrom(n) == false {
			continue
		}

		if isSumOfConsecutiveSquares(n) == false {
			continue
		}

		sum += int64(n)

	}

	fmt.Println(sum)

}

