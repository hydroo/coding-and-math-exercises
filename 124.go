package main

import (
	"fmt"
)


func rad(n int) int {

	product := 1
	used := make(map[int]bool)

	for i := 2; n > 1; i += 1 {

		if n % i == 0 {

			if _, ok := used[i]; ok == false {
				product *= i
			}

			n /= i

			used[i] = true

			i -= 1
			continue
		}

	}

	return product
}


func main() {

	min := 1
	max := 100000

	for n := min; n <= max; n += 1 {

		fmt.Printf("%07.0f %v\n",float64(rad(n)), n)
	}

	// then sort using bash or vim

}
