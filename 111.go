package main

import (
	"big"
	"fmt"
	"math"
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





func main() {

	min := int64(1000000001)
	max := int64(9999999999)

	fmt.Println("== ",min," - ",max," ==")


	digits := []int{'0','1','2','3','4','5','6','7','8','9'}


	maxMap := make(map[int]int)

	for _, digit := range digits {
		maxMap[digit] = 0
	}


	sumMap := make(map[int]*big.Int)
	for _, digit := range digits {
		sumMap[digit] = big.NewInt(0)
	}


	count := 0


	prime := big.NewInt(0)


	for n := min; n <= max; n += 2 {

		if isPrime(n) == false {
			continue
		}

		count += 1

		if count % 100000 == 0{
			fmt.Println(n)
		}

		prime.SetInt64(n)

		counts := make(map[int]int)

		for _, digit := range fmt.Sprint(prime){
			counts[digit] += 1
		}

		for digit, count := range counts {
			
			if maxMap[digit] < count {
				maxMap[digit] = count
				sumMap[digit].Set(prime)
			} else if maxMap[digit] == count {
				sumMap[digit].Add(sumMap[digit], prime)
			}
		}

	}

	sumsum := big.NewInt(0)

	for _, digit := range digits {

		sumsum.Add(sumsum, sumMap[digit])

		fmt.Printf("%c max: %d, sum: %d\n", digit, maxMap[digit], sumMap[digit])
	}

	fmt.Println("sumsum:", sumsum)

}

