package main

import (
	"fmt"
	"math"
)


func main() {
	fmt.Print("")


	minDeviation := 2000000


	sumOfIs := 0
	for i := 1; sumOfIs < 3000000; i += 1 {
		sumOfIs += i

		sumOfJs := sumOfIs-i
		for j := i ; sumOfJs < 3000000; j += 1 {
			sumOfJs += j

			//fmt.Println(sumOfIs, sumOfJs)

			product := sumOfIs*sumOfJs

			deviation := int(math.Fabs(float64(2000000-product)))


			if deviation < minDeviation {
				fmt.Println("  ",deviation, i, j)

				minDeviation = deviation
			}

		}
	}

}
