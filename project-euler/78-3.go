package main

import (
	"fmt"
)


type ResultMap map[int]int64

func (this ResultMap) get(k int) (int64, bool) {

	if k < 0 {
		return 0, false
	} else if k == 0 {
		return 1, true
	} else {
		ret1, ret2 := this[k]
		return ret1, ret2
	}

	panic("")
}


func recursiveSum(n int, modulo int64, resultMap ResultMap) int64 {

	if v, ok := resultMap.get(n); ok == true {
		return v
	}

	var sum int64 = 0

	for k := 1;; k+= 1 {

		n1 := n - (k*(3*k-1))/2
		n2 := n - (k*(3*k+1))/2

		if n1 < 0 && n2 < 0  {
			break
		}

		if k % 2 == 1 {
			sum += recursiveSum(n1, modulo, resultMap)
			sum += recursiveSum(n2, modulo, resultMap)
		} else {
			sum -= recursiveSum(n1, modulo, resultMap)
			sum -= recursiveSum(n2, modulo, resultMap)
		}
		
	}

	resultMap[n] = sum % modulo

	return sum % modulo
}


func main() {

	min := 2
	max := int(^uint32(0)>>1)

	resultMap := make(ResultMap)


	for i := min; i <= max; i++ {

		count := recursiveSum(i, 1000000, resultMap)

		fmt.Println(i, count)

		if count == 0 {
			panic("")
		}
	}

}

