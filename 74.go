package main

import (
	"fmt"
)


func Factorial(a uint64) uint64 {
	if a <= 1 {
		return 1
	} /* else { */
		return a * Factorial(a-1)
	/* } */
}


func SumOfFactorialsOfDigits(a uint64) uint64 {

	s := fmt.Sprint(a)
	sum := uint64(0)

	for _,c := range(s) {
		sum += Factorial(uint64(c-'0'))
	}

	return sum
}


func ChainOfLength60(a uint64) bool {

	values := make(map[uint64]bool)

	b := a
	length := 0

	for {

		values[b] = true

		b = SumOfFactorialsOfDigits(b)
		length += 1

		_, exists := values[b]

		if exists == true {
			break
		}

	}

	//fmt.Println(a, length)

	return length == 60
}


func main() {

	sum := 0

	for a:=uint64(2); a<1000000; a+=1 {
		if ChainOfLength60(a) == true {
			sum += 1
			fmt.Println(a, sum)
		}
	}
}
