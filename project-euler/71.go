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

	currentMin := Fraction{int64(0),int64(1)}
	max := Fraction{int64(3),int64(7)}

	for d := int64(1000000); d > int64(1); d-=int64(1) {

		for n := int64(d-1); n > 1; n-=int64(1) {

			if Gcd(d,n) == 1 {

				possibleNewMin := Fraction{n,d}

				if possibleNewMin.lowerThan(currentMin) &&
						max.lowerThan(possibleNewMin) {

					currentMin = possibleNewMin

					fmt.Println(currentMin)
				}
			}

		}
	}
}

