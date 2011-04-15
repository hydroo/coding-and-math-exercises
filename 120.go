package main

import (
	"big"
	"fmt"
)


func formula(a, n int64) int64 {

	mod := big.NewInt(a*a)

	bigN := big.NewInt(n)
	aMinusOne := big.NewInt(a-1)
	aPlusOne := big.NewInt(a+1)

	minus := big.NewInt(0)
	plus := big.NewInt(0)

	minus.Exp(aMinusOne, bigN, mod)
	plus.Exp(aPlusOne, bigN, mod)

	plus.Add(plus, minus)

	plus.Mod(plus, mod) 

	return plus.Int64()
}


func main() {

	sumR := int64(0)

	for a := int64(3); a <= 1000; a += 1 {

		bestR := int64(0)

		n := int64(1)
		for ; n <= 20000; n += 1 {

			r := formula(a, n)

			if r > bestR {
				bestR = r
			}

		}

		fmt.Println(a, bestR)

		sumR += bestR
	}

	fmt.Println(sumR)
}
