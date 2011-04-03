package main

import (
	"fmt"
)


type Triple struct {
	a, b, c, length uint64
}


func gcd(a uint64, b uint64) uint64 {

	for b != 0 {
		t := b
		b = a % b
		a = t
	}
	
	return a
}


func generatePythagoreanTriple(maxLength uint64, out chan<- Triple) {

	var m, n, a, b, c uint64

	for m = 2; 2*m*m + 2*m <= maxLength;m += 1 {

		for n = 1; n < m ;n += 1 {

			a = m*m - n*n
			b = 2*m*n
			c = m*m + n*n

			if a+b+c > maxLength {
				break
			}

			if gcd(a,b) == 1 && gcd(b,c) == 1 && gcd(a,c) == 1 {

				length := a+b+c

				for factor := uint64(1); length*factor <= maxLength; factor+=1 {
					out <- Triple{a*factor,b*factor,c*factor,length*factor}
				}

			}

		}
	}
}


func main() {

	var pythagoreanTriples = make(chan Triple, 1000)

	go generatePythagoreanTriple(1500000, pythagoreanTriples)

	lengths := make(map[uint64]uint64)
	count := 0

	for triple := range pythagoreanTriples {

		lengths[triple.length] += 1

		if lengths[triple.length] == 1 {
			count += 1
		} else if lengths[triple.length] == 2 {
			count -= 1
		}

		fmt.Println(count, triple)
	}

}

