package main

import (
	"container/vector"
	"fmt"
	"math"
)


func isPrime(n int) bool {

	if n == 2 {
		return true
	} else if n < 2 || n % 2 == 0 {
		return false
	}

	max := int(math.Sqrt(float64(n))) + 1

	for i := int(3); i <= max; i+=2 {
		if n % i == 0 {
			return false
		}
	}
		
	return true
}


func generatePrimes(min int, max int) vector.IntVector {

	var ret vector.IntVector

	for n := min; n <= max; n++ {
		if isPrime(n) {
			ret.Push(n)
		}
	}

	return ret
}


func main() {

	fmt.Print("")

	fiftyMillion := int64(50000000)

	results := make(map[int64]bool)

	var primes []int = generatePrimes(2,10000)

	for _, a := range primes {

		aa := int64(a)*int64(a)

		if aa >= fiftyMillion {
			break
		}

		for _, b := range primes {

			bbb := int64(b)*int64(b)*int64(b)

			if aa + bbb >= fiftyMillion {
				break
			}

			for _, c := range primes {

				cccc := int64(c)*int64(c)*int64(c)*int64(c)

				if aa + bbb + cccc >= fiftyMillion {
					break
				} else {
					results[aa+bbb+cccc] = true
				}

			}
		}
	}

	fmt.Println(len(results))
}

