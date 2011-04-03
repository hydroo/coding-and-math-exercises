package main

import (
	"fmt"
)


func u(n int64) int64 {

	n9 := -1 + n
	n8 :=  1 + n*n9
	n7 := -1 + n*n8
	n6 :=  1 + n*n7
	n5 := -1 + n*n6
	n4 :=  1 + n*n5
	n3 := -1 + n*n4
	n2 :=  1 + n*n3
	n1 := -1 + n*n2
	n0 :=  1 + n*n1

	return n0
}


func newton(x int64, Nk int64, givenX []int64) int64 {

	if int64(len(givenX)) < Nk-1 {
		panic("too few givenX")
	}

	ret := int64(1)

	for i := int64(1); i <= Nk; i += int64(1) {
		ret = ret*(x - givenX[i-1])
	}

	return ret
}


func calculateCoefficients(x []int64, y []int64) []int64 {
	l := len(x)
	ret := make([]int64,l)

	if l < 1 {
		return ret
	}


	right := make([][]int64, l)
	right[0] = make([]int64, l)
	for k, v := range y {
		right[0][k] = int64(v)
	}


	for i := 1; i < l; i += 1 {

		right[i] = make([]int64, l-i)

		for j := 0; j < l-i; j += 1 {

			num := right[i-1][j+1]-right[i-1][j]
			den := x[j+i]-x[j]

			right[i][j] = num/den

		}
	}

	for i := 0; i < l; i += 1 {
		ret[i] = right[i][0]
	}

	return ret
}


func main() {

	n := 11

	x := make([]int64, n)
	y := make([]int64, n)
	for i := 0; i < n; i += 1 {
		x[i] = int64(i+1)
		y[i] = u(int64(i+1))
	}

	c := calculateCoefficients(x, y)

	fmt.Println(x)
	fmt.Println(y)
	fmt.Println(c)

	FITsum := int64(0)

	
	for k := int64(1); k <= int64(n);k += int64(1) {

		sum := int64(0)

		fmt.Println(k,": approx", k+1)

		for i := int64(0); i < k; i += 1 {

			//sumTmp := sum

			sum += c[i] * newton(k+1, i, x)

			//fmt.Println("    ", sumTmp, "+=",c[i],"*",newton(k,i,x),"=",sum)

		}

		if sum != u(k+1) {
			fmt.Println("  ", sum, "should be", u(k+1))
			FITsum += sum
		} else {
			fmt.Println("  ", sum, "match!!! we're done: FITsum", FITsum)
		}


	}
}


