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


func phi(factors map[int]int) float64 {

	ret := float64(1)
	
	for p, v := range factors {

		ret *= float64(p-1)*math.Pow(float64(p), float64(v-1))
	}

	return ret
}


func main() {

	count := int64(0)

	min := 2
	max := 1000000

	primes := generatePrimes(min, max)

	nChannel := make(chan nWithFactors, 1000)

	go generateFactorizedN(primes, 0, max, 1, map[int]int{}, nChannel)

	for n := range nChannel {

		count += int64(phi(n.factors))

		fmt.Println(n.n, count)

	}
}

