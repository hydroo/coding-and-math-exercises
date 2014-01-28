package main

import (
	"fmt"
	"math"
)


type aAndB struct {
	a,b uint64
}

type Triangle struct {
	a,b,c,length uint64
}


func workerGeneral(mod uint64, in <-chan aAndB, out chan<- Triangle) {
	var aa, bb, cc uint64
	var cFloat float64;
	
	for value := range in {
		aa, bb = value.a*value.a, value.b*value.b

		cc = aa + bb

		if cc % 4 != mod { continue }
		
		cFloat = math.Sqrt(float64(cc))

		if math.Ceil(cFloat) != cFloat { continue }
		
		out <- Triangle{value.a, value.b, uint64(cFloat),value.a+value.b+uint64(cFloat)}
	}
}


func workerEvenEven(in <-chan aAndB, out chan<- Triangle) {
	workerGeneral(0, in, out)
}


func workerEvenOdd(in <-chan aAndB, out chan<- Triangle) {
	workerGeneral(1, in, out)
}


func workerOddOdd(in <-chan aAndB, out chan<- Triangle) {
	workerGeneral(2, in, out)
}


func generator(maxLength float64, outEvenEven, outEvenOdd, outOddOdd chan<- aAndB) {

	var a,b uint64

	var invSqrtOf2 float64 = 1.0 / math.Sqrt(2)

	var evenHalfLength uint64 = uint64(maxLength*invSqrtOf2 + float64(uint64(maxLength*invSqrtOf2) % 2))
	var halfEvenHalfLength uint64 = uint64(float64(evenHalfLength)*invSqrtOf2)

	for a = 2; a <= halfEvenHalfLength; a+=2 {

		b = a

		outEvenEven <- aAndB{a,b}
		outEvenOdd <- aAndB{a,b+1}
		outOddOdd <- aAndB{a+1,b+1}

		//fmt.Println("    ", aAndB{a,b}, aAndB{a,b+1}, aAndB{a+1,b+1})

		for b = a+2; b <= evenHalfLength-a; b+=2 {

			outEvenEven <- aAndB{a,b}
			outEvenOdd <- aAndB{a,b+1}
			outEvenOdd <- aAndB{a+1,b}
			outOddOdd <- aAndB{a+1,b+1}

			//fmt.Println("    ", aAndB{a,b}, aAndB{a,b+1}, aAndB{a+1,b}, aAndB{a+1,b+1})
		}
	}

}

func main() {

	inEvenEven := make(chan aAndB, 100000)
	inEvenOdd := make(chan aAndB, 100000)
	inOddOdd := make(chan aAndB, 100000)
	out := make(chan Triangle, 100000)

	for workerCount := 0; workerCount < 8; workerCount+=1 {
		go workerEvenEven(inEvenEven, out)
		go workerEvenOdd(inEvenOdd, out)
		go workerOddOdd(inOddOdd, out)
	}

	var maxLength uint64 = 1500000

	go generator(float64(maxLength), inEvenEven, inEvenOdd, inOddOdd)


	lengths := make(map[uint64]uint64)

	var count uint64 = 0

	for result := range out {
		if result.length > maxLength { continue }
		
		lengths[result.length] += 1

		if lengths[result.length] == 1 {
			count += 1
		} else if lengths[result.length] == 2 {
			count -= 1
		}

		fmt.Println(count, result)
	}

	fmt.Println(count)
}
