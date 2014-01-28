package main

import (
	"fmt"
	"math"
	"time"
)

type dAndX struct {
	D int64
	x int64
}


func isSquare(a int64) bool {
	return math.Sqrt(float64(a)) == math.Floor(math.Sqrt(float64(a)))
}


func comparator(in <-chan dAndX, end chan<- bool) {

	var largestX int64 = 0
	var newDAndX dAndX

	for i := 0; i < 1001; i++ {
		
		if isSquare(i) { continue }

		newDAndX = <-in

		if newDAndX.x > largestX {
			largestX = newDAndX.x
			
			fmt.Println(i, newDAndX.D, largestX)
		}
	}

	end<- true
}


func forEachD(D int64, returnChannel chan<- dAndX) {

	for yIterator := int64(1);; yIterator++ {

		if yIterator % 10000000 == 0 { time.Sleep(1) }

		y := yIterator*yIterator;

		x := int64(math.Sqrt(1+D*y))

			rest := x - D*y

			if rest != 0 {
				break
			} else {
				returnChannel <- dAndX{D, xIterator}
				return
			}

		}

	}
}



func main() {

	returnChannel := make(chan dAndX)
	endChannel := make(chan bool)

	go comparator(returnChannel, endChannel)

	for D := int64(1); D < 1001; D++ {

		if isSquare(D) { continue }

		go forEachD(D, returnChannel)

	}

	<-endChannel
}

