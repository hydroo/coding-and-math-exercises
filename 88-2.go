package main

import (
	"container/vector"
	"fmt"
	"math"
	"sort"
)


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


func copyMapIntInt(m map[int]int) map[int]int {

	ret := make(map[int]int)

	for k, v := range m {
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


func generateEquivalentProducts(expandedProduct []int) [][]int {

	resultMap := make(map[string][]int)

	generateEquivalentProductsRecursive(expandedProduct, resultMap)


	ret := make([][]int,len(resultMap))
	i := 0
	for _, v := range resultMap {
		ret[i] = v
		i += 1
	}

	return ret
}


func generateEquivalentProductsRecursive(product []int, resultMap map[string][]int) {

	productString := fmt.Sprint(product)
	if _, ok := resultMap[productString]; ok == true {
		return
	}
	resultMap[productString] = product

	done := make(map[int]bool)

	for i := 0; i < len(product); i += 1 {
		for j := i+1; j < len(product); j += 1 {

			p := product[i] * product[j]

			done[p] = true

			productTmp := vector.IntVector(product)
			productCopy := productTmp.Copy()

			productCopy.Delete(j)
			productCopy.Set(i,p)

			sort.SortInts(productCopy)

			generateEquivalentProductsRecursive(productCopy, resultMap)

		}
	}
}


func isProductSum(product []int) (k int) {

	sum := 0
	prod := 1

	for _, v := range product {
		sum += v
		prod *= v
	}

	if prod-sum >= 0 {
		return len(product) + (prod - sum)
	}

	return -1
}


func main() {
	fmt.Println()

	min := 2
	max := 15000

	kToProductSum := make([]int,12000+1)
	for k, _ := range kToProductSum {
		kToProductSum[k] = 0x7fffffff
	}


	factorizedNumbers := generateAllNumbers(min,max)

	for number, factorization := range factorizedNumbers {

		expandedProduct := expandFactorization(factorization)
		sort.SortInts(expandedProduct)

		fmt.Println(number, "==", expandedProduct)

		products := generateEquivalentProducts(expandedProduct)

		for _, product := range products {


			k := isProductSum(product)

			fmt.Println("  ",k, product)

			if k <= 12000 {

				if kToProductSum[k] > number {
					kToProductSum[k] = number
				}
			}

		}
	}


	productSums := make(map[int]bool)
	for k, v := range kToProductSum {

		if k == 0 || k == 1 {
			continue
		}

		fmt.Println(k,v)

		productSums[v] = true
	}


	sumOfProductSums := uint64(0)
	for k, _ := range productSums {

		if k < 0 {
			panic("w00t")
		}

		sumOfProductSums += uint64(k)
	}

	fmt.Println(sumOfProductSums)

}

