package main

import (
	"fmt"
)


func gcd (a, b int) int {

	var ret int

	if a == 0 {
		ret = b
	} else {

		for ; b != 0; {
			if a > b {
				a -= b
			} else {
				b -= a
			}
		}
		ret = a
	}

	return ret
}


func lcm(a, b int) int {
	return a*b / gcd(a,b)
}


func main() {


	min := int64(720720)
	max := int64(10000000000)

	maxCount := int64(0)

	for n := min; n <= max; n += 1 {

		//fmt.Println(n,":")

		count := int64(0)

		for x := n + 1; x <= n*2; x += 1 {

			y := n*x / (x-n)

			if n*(x+y) < 0 {
				panic(fmt.Sprint("damn", n, n*(x+y)))
			}

			if n*(x+y) == x*y {
				count += 1
				//fmt.Println("  1/", n, " =  1/", x, " + 1/" ,y)
			}


		}

		if count > maxCount {
			fmt.Println(n, count)
			maxCount = count
		} else if n % 100000 == 0 {
			fmt.Println(n)
		}

		if count > 4000000 {
			fmt.Println(n)
			break
		}

	}

}

