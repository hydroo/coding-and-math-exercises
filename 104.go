package main

import (
	"big"
	"fmt"
)


func isPandigital(n int64) bool {
	
	m := make(map[int64]bool)

	if n >= 100000000 {

		digit := int64(0)
		for i := int64(100000000); i >= 1; i /= 10 {

			digit = n/i - (n/(i*10))*10

			//fmt.Println("  ", n/i, digit )

			if digit == 0 {
				return false
			} else {
				m[digit] = true
			}

		}



	}

	return len(m) == 9

	
}


func main() {
	
	fMinus1Mod := int64(1)
	fMinus2Mod := int64(1)
	var tmp int64

	fMinus1 := big.NewInt(int64(1))
	fMinus2 := big.NewInt(int64(1))
	tmpBig := big.NewInt(int64(1))

	for i := int64(3);; i += 1{

		tmp = fMinus1Mod
		fMinus1Mod = (fMinus1Mod + fMinus2Mod) % 1000000000
		fMinus2Mod = tmp

		tmpBig.Set(fMinus1)
		fMinus1.Add(fMinus1, fMinus2)
		fMinus2.Set(tmpBig)

		if isPandigital(fMinus1Mod) {

			var firstNineDigits int64
			s := fMinus1.String()[:9]

			_, error := fmt.Sscan(s, &firstNineDigits)
			if error != nil {
				panic(error)
			}

			fmt.Println(i, "last", fMinus1Mod, "! first", firstNineDigits)

			if isPandigital(firstNineDigits) {
				fmt.Println("w00t")
				break
			}

		}


	}
}

