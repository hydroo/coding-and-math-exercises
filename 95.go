package main

import (
	"container/vector"
	"fmt"
	"math"
	"sort"
)


func copyMapIntInt(m map[int]int) map[int]int {
	ret := make(map[int]int)
	for k, v := range m {
		ret[k] = v
	}
	return ret
}


func isPrime(n int) bool {

	if n == 2 {
		return true
	} else if n < 2 || n % 2 == 0 {
		return false
	}

	max := int(math.Sqrt(float64(n))) + 1

	for i := 3; i <= max; i+=2 {
		if n % i == 0 {
			return false
		}
	}
		
	return true
}


func generatePrimes(min int, max int) []int {

	var primes vector.IntVector

	for n := min; n <= max; n++ {
		if isPrime(n) {
			primes.Push(n)
		}
	}

	ret := make([]int,len(primes))
	for k, v := range primes {
		ret[k] = v
	}

	return ret
}




func generateNumbers(primes []int, pos int, max int, currentN int, currentFactors map[int]int, numbers map[int]map[int]int) {

	for ; pos < len(primes); pos++ {

		prime := primes[pos]

		pToThePowerOfKTimesN := currentN

		for k := 1;; k++ {

			if uint64(pToThePowerOfKTimesN) * uint64(prime) > uint64(max) {
				break
			}

			pToThePowerOfKTimesN *= prime

			copiedCurrentFactors := copyMapIntInt(currentFactors)
			copiedCurrentFactors[prime] = k

			numbers[pToThePowerOfKTimesN] = copyMapIntInt(copiedCurrentFactors)

			generateNumbers(primes, pos+1, max, pToThePowerOfKTimesN, copiedCurrentFactors, numbers)
		}
	}
}


func generateAllNumbers(min, max int) []map[int]int {

	primes := generatePrimes(min, max)

	numberMap := make(map[int]map[int]int)
	generateNumbers(primes, 0, max, 1, map[int]int{}, numberMap)

	ret := make([]map[int]int,len(numberMap)+2)

	for k, v := range numberMap {
		ret[k] = v
	}

	return ret
}


func expandFactorization(factorization map[int]int) []int {

	expSum := 0
	for _, v := range factorization {
		expSum += v
	}

	ret := make([]int, expSum)

	i1 := 0
	for k, v := range factorization {
		for i2 := 0; i2 < v; i2 += 1 {
			ret[i1+i2] = k
		}
		i1 += v
	}

	return ret
}


func generateDivisors(expandedProduct []int) []int {

	resultMap := make(map[int]bool)

	generateDivisorsRecursively(expandedProduct, 1, 0, resultMap)


	ret := make([]int,len(resultMap))
	i := 0
	for k, _ := range resultMap {
		ret[i] = k
		i += 1
	}

	sort.SortInts(ret)

	return ret[:len(ret)-1]
}


func generateDivisorsRecursively(product []int, currentProduct, currentIndex int, resultMap map[int]bool) {

	if currentIndex == len(product) {
		resultMap[currentProduct] = true
		return
	}

	generateDivisorsRecursively(product, currentProduct, currentIndex+1, resultMap)
	generateDivisorsRecursively(product, currentProduct*product[currentIndex], currentIndex+1, resultMap)
}


func main() {
	fmt.Println()

	min := 2
	max := 1000000

	largestChainLength := 0

	factorizedNumbers := generateAllNumbers(min,max)

	numberToDivisorSum := make(map[int]int)

	for number, factorization := range factorizedNumbers {

		expandedProduct := expandFactorization(factorization)
		//sort.SortInts(expandedProduct)

		divisors := generateDivisors(expandedProduct)

		divisorsum := 0

		for _, v := range divisors {
			divisorsum += v
		}

		numberToDivisorSum[number] = divisorsum

		fmt.Print(number, " ")

	}


	for number, divisorsum := range numberToDivisorSum {

		//fmt.Println(number)

		length := 1
		smallestElement := number

		next := divisorsum

		invalid := false

		visited := make(map[int]bool)
		visited[number] = true

		for {

			//fmt.Print(next, " ")

			if next > max {
				invalid = true
				break
			}

			if next == number {
				invalid = false
				break
			}

			if visited[next] == true {
				invalid = true
				break
			}

			if next < smallestElement {
				smallestElement = next
			}

			visited[next] = true

			next = numberToDivisorSum[next]

			length += 1

		}

		if invalid == false && length > largestChainLength {
			largestChainLength = length

			fmt.Println(number, length, smallestElement)
		}

	}



}

