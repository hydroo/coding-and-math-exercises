package main

import (
	"fmt"
	"container/vector"
)


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


func recursiveMerging(sum Sum, lastElement int, indexToChange int, count *uint64) {

	*count += 1

	if *count % 500000 == 0 {
		fmt.Println(*count, ":", sum)
	}

	for i := 2; i <= sum.Len() - indexToChange && i <= lastElement; i += 1 {
		recursiveMerging(sum.Merge(indexToChange,i), i, indexToChange+1, count)
	}
}


func main() {

	var a Sum
	var initVector vector.IntVector

	for i := 0; i < 100; i+=1 { initVector.Push(1) }

	a.Init(initVector)

	var count uint64 = 0

	recursiveMerging(a, 100, 0, &count)

	fmt.Println(count-1)
}

