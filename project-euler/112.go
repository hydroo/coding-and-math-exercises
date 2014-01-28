package main

import (
	"fmt"
)


func isBouncy(n int64) bool {

	inc := true
	dec := true

	lastInc := '0'
	lastDec := '9'

	for _, v := range fmt.Sprint(n) {

		if v < lastInc {
			inc = false
		}

		if v > lastDec {
			dec = false
		}

		lastInc = v
		lastDec = v
		
	}

	return inc == false && dec == false
}


func main() {

	count := int64(0)

	n := int64(0)
	for ; ; n += 1 {

		if isBouncy(n) == true {
			count += 1

			if float64(count) / float64(n) >= 0.99 {
				break
			}
		}
	}

	fmt.Println(n,float64(count)/float64(n))
}

