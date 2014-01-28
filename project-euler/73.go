package main

import (
	"fmt"
)

func Abs(a int64) int64 {
	if a >= 0 {
		return a
	}/* else {*/
		return a * -1
	/*}*/
}

func Gcd(a int64, b int64) int64 {

	for b != int64(0) {
		t := b
		b = a % b
		a = t
	}
	
	return a
}

func Lcm(a int64,b int64) int64 {
    return Abs(a*b) / Gcd(a,b)
}


type Fraction struct {
	n int64
	d int64
}

func (this Fraction) lowerThan(lower Fraction) bool {
	
	lcm := Lcm(this.d, lower.d)

	this2 := lcm*this.n/this.d
	lower2 := lcm*lower.n/lower.d

	//fmt.Println(this, lower, this2, lower2, lower2 < this2)

	return lower2 < this2
}


func main() {

	min := Fraction{int64(1),int64(3)}
	max := Fraction{int64(1),int64(2)}

	count := 0

	for d := int64(12000); d > int64(1); d-=int64(1) {

		for n := int64(d-1); n > 1; n-=int64(1) {

			if Gcd(d,n) == 1 {

				possibleMatch := Fraction{n,d}

				if possibleMatch.lowerThan(min) &&
						max.lowerThan(possibleMatch) {

					count+=1

					fmt.Println(possibleMatch, count)
				}
			}

		}
	}
}

