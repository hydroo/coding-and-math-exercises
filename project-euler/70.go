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


type nWithFactors struct {
	n int
	factors map[int]int
}


func copyMapIntInt(m map[int]int) map[int]int {

	ret := make(map[int]int)

	for k, v := range m {
		ret[k] = v
	}

	return ret
}


func generateFactorizedN(primes vector.IntVector, pos int, max int, currentN int, currentFactors map[int]int, returnChannel chan<-nWithFactors) {

	for ; pos < len(primes); pos++ {

		prime := primes.At(pos)

		pToThePowerOfKTimesN := currentN

		for k := 1;; k++ {

			if int64(pToThePowerOfKTimesN) * int64(prime) > int64(max) {
				break
			}

			pToThePowerOfKTimesN *= prime

			copiedCurrentFactors := copyMapIntInt(currentFactors)
			copiedCurrentFactors[prime] = k

			returnChannel<-nWithFactors{pToThePowerOfKTimesN, copiedCurrentFactors}
			generateFactorizedN(primes, pos+1, max, pToThePowerOfKTimesN, copiedCurrentFactors, returnChannel)
		}
	}
}


func phi(factors map[int]int) int {

	ret := 1
	
	for p, v := range factors {

		ret *= int(float64(p-1)*math.Pow(float64(p), float64(v-1)))
	}

	return ret
}


func isPermutation(n_ int, phi_ int) bool {

	n, phi := fmt.Sprint(n_), fmt.Sprint(phi_)

	if len(n) != len(phi) {
		return false
	}

	phiMap := make(map[int]int, len(phi))

	for _, v := range phi {
		phiMap[v-'0']++
	}

	for _, v := range n {
		phiMap[v-'0']--

		if phiMap[v-'0'] < 0 {
			return false
		}
	}

	return true
}


func main() {

	min := 2
	max := 10000000

	bestN := 2
	bestQuotient := float64(2)

	primes := generatePrimes(min, max)


	nChannel := make(chan nWithFactors, 1000)

	go generateFactorizedN(primes, 0, max, 1, map[int]int{}, nChannel)

	for n := range nChannel {

		phi_ := phi(n.factors)

		//fmt.Println(i, n.n, phi_, isPermutation(n.n, phi_))

		quotient := float64(n.n) / float64(phi_)

		if  quotient < bestQuotient && isPermutation(n.n, phi_) == true {
			bestQuotient = quotient
			bestN = n.n

			fmt.Println(bestN , phi_, bestQuotient)
		}
	}
}

