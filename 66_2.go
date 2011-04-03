package main

/* this implementation has a bug
	only if the rest of the continued fraction
	is odd or even (one of this) the results are
	correct. The wrong case is that x*x-D*y*y=-1 is solved */

import (
	"fmt"
	"math"
	//"time"
	"container/vector"
)

type dAndX struct {
	D int
	x int64
	y int64
	chainLen int
}


var minD = 2
var maxD = 1001


func isSquare(a int) bool {
	return math.Sqrt(float64(a)) == math.Floor(math.Sqrt(float64(a)))
}


func comparator(in <-chan dAndX, end chan<- bool) {

	var largestX int64 = 0
	var newDAndX dAndX

	for i := minD; i <= maxD+1; i++ {
		
		if isSquare(i) { continue }

		newDAndX = <-in

		if newDAndX.x < 0 {fmt.Println(":/", newDAndX.D, newDAndX.chainLen)}

		if newDAndX.x > largestX {
			largestX = newDAndX.x
			
			fmt.Println("--",i, newDAndX.D, largestX)
		}
	}

	end<- true
}


func continuedFraction(a float64, dSquaredFloorTimesTwo int) vector.IntVector {

	aFloor := int(math.Floor(a))

	var ret vector.IntVector

	if dSquaredFloorTimesTwo == aFloor { return ret }

	ret.Push(aFloor)

	nextRet := continuedFraction(1/(a-float64(aFloor)), dSquaredFloorTimesTwo)

	ret.AppendVector(&nextRet)

	return ret
}


func rationalFromContinuedFraction(chain []int) (int64, int64, int) {

	var numerator, denominator int64

	numerator = int64(chain[len(chain)-1])
	denominator = int64(1)

	for i := len(chain)-1; i>0; i-- {

		newDenominator := int64(chain[i-1])*denominator+numerator
		newNumerator := denominator

		denominator = newDenominator
		numerator = newNumerator

	}

	return numerator, denominator, len(chain)
}


func forEachD(D int, returnChannel chan<- dAndX) {

	cFrac := continuedFraction(math.Sqrt(float64(D)), 2*int(math.Floor(math.Sqrt(float64(D)))))

	x, y, chainLen:= rationalFromContinuedFraction(cFrac)

	//fmt.Println(D, x, y)

	returnChannel<-dAndX{D,x, y, chainLen}


}



func main() {

	returnChannel := make(chan dAndX)
	endChannel := make(chan bool)

	go comparator(returnChannel, endChannel)

	for D := minD; D <= maxD; D++ {

		if isSquare(D) { continue }

		go forEachD(D, returnChannel)

	}

	<-endChannel
}

