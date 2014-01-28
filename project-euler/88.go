package main

import (
	"fmt"
)


// 1x2x3 = 1+2+3, k=3,n1=1,count=1,n2=2,count=1,n3=3,count=1

type productSumNumber struct {
	vector []uint64
}


func newProductSumNumber(k int) productSumNumber {
	var ret productSumNumber
	ret.vector = make([]uint64, k)
	for i := range ret.vector {
		ret.vector[i] = 1
	}

	ret.vector[0] = 2
	ret.vector[1] = 2

	return ret
}


func (this productSumNumber) Sum() uint64 {
	ret := uint64(0)
	for _, v := range this.vector {
		ret += v
	}
	return ret
}


func (this productSumNumber) Product() uint64 {
	ret := uint64(1)
	for _, v := range this.vector {
		ret *= v
	}
	return ret
}


func (this productSumNumber) Len() int {
	return len(this.vector)
}


func (this productSumNumber) Print() {
	fmt.Print("[")
	for _, v := range this.vector {
		fmt.Print(v," ")
		if v == 1 {
			break
		}
	}
	fmt.Print("]")
}


func iterate(this productSumNumber, firstVariableIndex int, min uint64, max uint64) (finished bool, ret productSumNumber) {

	//fmt.Println("  *",this.Product(),", +",this.Sum()," ,",this.vector)


	tmpThisVar := this.vector[firstVariableIndex]

	for this.Product() < this.Sum() && this.vector[firstVariableIndex] < max {
		this.vector[firstVariableIndex] += 1
	}

	maxVar := this.vector[firstVariableIndex]
	this.vector[firstVariableIndex] = tmpThisVar

	for ; this.vector[firstVariableIndex] <= maxVar; this.vector[firstVariableIndex] += 1 {

		if this.Product() == this.Sum() {
			return true, this
		}

		if firstVariableIndex+1 < len(this.vector) {

			this2 := newProductSumNumber(len(this.vector))
			copy(this2.vector, this.vector)

			var min uint64

			if firstVariableIndex+2 >= len(this.vector) {
				min = 1
			} else {
				min = this.vector[firstVariableIndex+2]
			}

			fin, ret := iterate(this2, firstVariableIndex+1, min, this.vector[firstVariableIndex])

			if fin == true {
				return true, ret
			}

		}

	}

	return false, this

}


func productSumFromScratch(k int) productSumNumber {

	_, ret := iterate(newProductSumNumber(k), 0, 1, uint64(0xffffffffffffffff))

	return ret
}


func expansions(vec []uint64, sumToLens map[uint64]map[int]bool, prevL int, ret map[int]bool) {


	for i, v := range vec {

		if v < 2 {
			break
		}

		for l,_ := range sumToLens[v] {

			realL := l + prevL

			ret[realL] = true

			vec2 := make([]uint64,len(vec))
			copy(vec2,vec)
			vec2[i] = 2

			expansions(vec2,sumToLens,realL-1,ret)

		}

	}
	//fmt.Println(ret)
}


func main() {

	sumToLens := make(map[uint64]map[int]bool)
	kToSum := make(map[int]uint64)

	for k := 2; k <= 12000; k += 1 {

		sum, found := kToSum[k]
		found = false
		psn := newProductSumNumber(k)

		if found == false {
			psn = productSumFromScratch(k)
			sum = psn.Sum()

			kToSum[k] = sum

			if _, ok := sumToLens[sum]; ok == false {
				sumToLens[sum] = make(map[int]bool)
			}

			sumToLens[sum][k] = true

			expansionsMap := make(map[int]bool)
			expansions(psn.vector, sumToLens, 0, expansionsMap)

			for v, _ := range expansionsMap {
				kToSum[k+v-1] = sum
				sumToLens[sum][k+v-1] = true
			}


		} else {
			/* done */
		}

		if found {
			fmt.Println(k, sum, "-" /*,psn*/ )
		} else {
			fmt.Print(k, sum)
			psn.Print()
			fmt.Print("\n")
		}

	}


	sum := uint64(0)
	for k, _ := range sumToLens {
		sum += k
	}

	fmt.Println("\n\n")
	fmt.Println("sum:", sum)
	fmt.Println("kToSum:", len(kToSum), kToSum)
	fmt.Println("sumToLens:", len(sumToLens), sumToLens)

}
