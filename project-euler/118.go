package main

import (
	"container/vector"
	"fmt"
	"math"
	"sort"
)


func isPrime(n int64) bool {

	if n == 2 {
		return true
	} else if n < 2 || n % 2 == 0 {
		return false
	}

	max := int64(math.Sqrt(float64(n))) + 1

	for i := int64(3); i <= max; i+=2 {
		if n % i == 0 {
			return false
		}
	}
		
	return true
}


func generatePrimes() [][]string {

	done := make(map[int]bool)
	results := make(map[int64]bool)

	generatePrimesRecursively(0, 0, done, results)

	ret := make([][]string, 10)
	ret[0] = make([]string,0)

	min := int64(1)
	max := int64(1)

	for i := 1; i < 10; i += 1 {

		max *= 10

		resultsLenN := make(map[int64]bool)

		for k, _ := range results {
			if k >= min && k < max {
				resultsLenN[k] = true
				results[k] = false, false
			}
		}

		strings := make([]string, len(resultsLenN))

		j := 0
		for k, _ := range resultsLenN {
			strings[j] = fmt.Sprint(k)
			j += 1
		}

		sort.SortStrings(strings)

		ret[i] = strings

		min *= 10

	}

	if len(results) > 0 {
		panic("len(results) > 0 ... w00t")
	}

	return ret
}
func generatePrimesRecursively(current int64, exponent int, done map[int]bool, results map[int64]bool) {

	if _, ok := results[current]; ok == false {

		if isPrime(current) == true {
			results[current] = true
		}
	}

	factor := int64(1)
	for i := 0; i < exponent; i += 1 { factor *= 10 }

	for i := 1; i <= 9; i += 1 {
		if _, ok := done[i]; ok == false {

			doneCopy := make(map[int]bool)
			for k, v := range done {
				doneCopy[k] = v
			}
			doneCopy[i] = true

			generatePrimesRecursively(current+int64(i)*factor, exponent+1, doneCopy, results)

		}
	}

}


func joinDigitMaps(a,b map[int]bool) map[int]bool {
	c := make(map[int]bool)

	for k, v := range a {
		c[k] = v
	}

	for k, v := range b {
		c[k] = v
	}

	return c
}


func countSets(primes [][]map[int]bool, primesByLen [][]string) int64 {

	var current vector.StringVector
	usedDigits := make(map[int]bool)

	return countSetsRecursively(-1, -1, current, usedDigits, primes, primesByLen)
}
func countSetsRecursively(lastLen, lastK int, current vector.StringVector, usedDigits map[int]bool,
		primes [][]map[int]bool, primesByLen [][]string) int64 {

	currentLength := len(usedDigits)

	if currentLength == 9 {
		//fmt.Println(current)
		return 1
	} else if currentLength > 9 {
		panic("w00t")
	}

	count := int64(0)


	for length, v := range primes {

		if currentLength + length > 9 {
			break
		}

		if length < lastLen {
			continue
		}

		for k, digits := range v {
			
			if k <= lastK {
				continue
			}

			joinedDigits := joinDigitMaps(usedDigits, digits)

			if len(joinedDigits) == currentLength + len(digits) {

				currentCopy := current.Copy()
				currentCopy.Push(primesByLen[length][k])

				count += countSetsRecursively(length, k, currentCopy, joinedDigits, primes, primesByLen)

			}

		}

		lastK = -1

	}

	return count
	
}


func main() {
	primesByLen := generatePrimes()

	primes := make([][]map[int]bool, 10)
	for length, v := range primesByLen {
		primes[length] = make([]map[int]bool, len(v))

		for k, prime := range v {

			primes[length][k] = make(map[int]bool)
			
			for _, digit := range prime {
				primes[length][k][digit-'0'] = true
			}

			//fmt.Println(length, prime, primes[length][k])
		}
	}

	count := countSets(primes, primesByLen)

	fmt.Println(count)

}

