package main

import (
	"fmt"
	"math"
	"os"
)


func main() {

	file, error := os.Open("99.txt", os.O_RDONLY, 0666)
	if error != nil {
		panic("cannot open input file \"96.txt\"")
	}
	defer file.Close()


	largestBase := float64(0)
	largestExp := float64(0)

	for i := 1;; i += 1 {
		var base, exp float64

		read, error := fmt.Fscanln(file, &base, &exp)
		if read == 0 || error != nil {
			break
		}

		quotient := exp / largestExp

		compare := math.Pow(base,quotient)

		if compare > largestBase {
			largestBase = base
			largestExp = exp

			fmt.Println(i, base, exp)
		}




	}


}

