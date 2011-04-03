package main

import (
	"container/vector"
	"fmt"
	"math"
)


func isPrime(n int) bool {

	if n == 2 {
		return true
	} else if n < 2 || n % 2 == 0 {
		return false
	}

	max := int(math.Sqrt(float64(n))) + 1

	for i := int(3); i <= max; i+=2 {
		if n % i == 0 {
			return false
		}
	}
		
	return true
}


type Sum struct {
	elements vector.IntVector
}


func (this *Sum) Init(newElements vector.IntVector) {
	this.elements = newElements.Copy()
}


func (this Sum) String() string {

	var ret string

	for _, v := range this.elements {
		ret += fmt.Sprint(v) + " "
	}

	return ret
}


func (this Sum) Len() int {
	return len(this.elements)
}


func (this Sum) IsSorted() bool {

	if this.Len() <= 1 { return true }

	var last int = this.elements[0]

	for _,v := range this.elements {
		if last < v { return false}
		last = v
	}

	return true
}


func (this Sum) Merge(from int, length int) Sum {

	var ret Sum

	for i := 0; i < from; i += 1 {
		ret.elements.Push(this.elements[i])
	}

	ret.elements.Push(length)

	for i := from+length; i < this.Len(); i += 1 {
		ret.elements.Push(this.elements[i])
	}

	return ret
}


func recursiveMerging(sum Sum, lastElement int, indexToChange int, count *uint64, primes map[int]bool) {

	if sum.elements[len(sum.elements)-1] > 1 {
		*count += 1
	}

	for i := 2; i <= sum.Len() - indexToChange && i <= lastElement; i += 1 {
		if primes[i] == true {
			recursiveMerging(sum.Merge(indexToChange,i), i, indexToChange+1, count, primes)
		}
	}
}


func main() {

	min := 2
	max := int(^uint32(0)>>1)

	primes := make(map[int]bool)

	fmt.Println(max)

	for currentSum := min; currentSum <= max; currentSum++ {

		if isPrime(currentSum) == true {
			primes[currentSum] = true
		}

		var a Sum
		var initVector vector.IntVector

		for i := 0; i < currentSum; i+=1 { initVector.Push(1) }

		a.Init(initVector)

		var count uint64 = 0

		recursiveMerging(a, currentSum, 0, &count, primes)

		fmt.Println(currentSum, count)

		if count > 5000 {
			panic(currentSum)
		}
	}
}

