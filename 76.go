package main

import (
	"fmt"
	"container/vector"
)


type Sum struct {
	elements vector.IntVector
	accumulated int
}


func (this *Sum) Init(newElements vector.IntVector) {
	this.elements = newElements.Copy()

	this.accumulated = 0
	for _,v := range this.elements {
		this.accumulated += v
	}
}


func (this *Sum) Init2(newElements vector.IntVector, newAccumulated int) {
	this.elements = newElements.Copy()
	this.accumulated = newAccumulated
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


func (this Sum) Accumulated() int {
	return this.accumulated
}


func (this Sum) WouldBeSorted(splitIndex int) bool {
	
	if (splitIndex < 1 || splitIndex > this.accumulated-1) { return false }

	for k,v := range this.elements {
		splitIndex -= v

		if splitIndex > 0 {
			continue
		} else if splitIndex == 0 {
			return false
		} else {

			newK := v+splitIndex
			newL := splitIndex*-1

			if newK < newL { return false }

			if k > 0 {
				preK := this.elements[k-1]
				if preK < newK { return false }
			}
			
			if k < this.Len()-1 && this.Len() > 1 {
				postL := this.elements[k+1]
				if newL < postL { return false }
			}

			return true
		}
	}

	panic("should never happen")
}


func (this Sum) Split(index int) Sum {

	var ret2 Sum

	for k,v := range this.elements {
		index -= v

		if index > 0 {
			continue
		} else if index == 0 {
			panic("")
		} else {
			ret2.Init2(this.elements, this.accumulated)
			ret2.elements[k] += index
			ret2.elements.Insert(k+1, index*-1)
			return ret2
		}
	}

	panic("should never happen")
}


func recursiveSplit(sum Sum, variants map[string]bool) {

	str := sum.String()

	if _,ok := variants[str]; ok == false {
		variants[str] = true
		fmt.Println(len(variants), sum)
	}

	maxIndex := sum.Accumulated()

	for i := (maxIndex)/2-1; i < maxIndex; i += 1 {
		
		if sum.WouldBeSorted(i) {
			recursiveSplit(sum.Split(i), variants)
		}
	}

}


func main() {

	var a Sum

	variants := make(map[string]bool)

	a.Init(vector.IntVector{100})

	recursiveSplit(a, variants)

	fmt.Println(len(variants))
}

