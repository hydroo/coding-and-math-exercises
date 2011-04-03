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


func (this Sum) isX() bool {
	last, nextToLast := this.elements[len(this.elements)-1], this.elements[len(this.elements)-2]
	return nextToLast > last
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


func recursiveMerging(sum Sum, lastElement int, indexToChange int) (count, x uint64 ){

	//fmt.Println(sum)

	var ret uint64 = 1
	var ret2 uint64 = 0

	if sum.Len() == 1 || sum.isX() {
		ret2 = 1
	}

	for i := 2; i <= sum.Len() - indexToChange && i <= lastElement; i += 1 {
		addToRet, addToRet2 := recursiveMerging(sum.Merge(indexToChange,i), i, indexToChange+1)
		ret += addToRet
		ret2 += addToRet2
	}

	return ret, ret2
}


func main() {

	min := 2
	max := 13//int(^uint32(0)>>1)


	for currentSum := min; currentSum <= max; currentSum++ {
		var a Sum
		var initVector vector.IntVector

		for i := 0; i < currentSum; i+=1 { initVector.Push(1) }

		a.Init(initVector)

		count, x := recursiveMerging(a, currentSum, 0)

		fmt.Println(currentSum, ":", count, x)

		if count % 1000000 == 0 {
			panic("")
		}
	}

}

