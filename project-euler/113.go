package main

import (
	"fmt"
)


const log int = 100


func countInc(stelle int, val int, mapInc map[int]map[int]int64) int64 {

	if stelle == log {
		//fmt.Println(n)
		return 1
	} else if v, ok := mapInc[stelle][val]; ok == true {
		return v
	}

	ret := int64(0)

	for i := val; i <= 9; i += 1 {
		ret += countInc(stelle + 1, i, mapInc)
	}

	mapInc[stelle][val] = ret

	return ret
}


func countDec(stelle int, val int, mapDec map[int]map[int]int64) int64 {

	if stelle == log {
		return 1
	} else if v, ok := mapDec[stelle][val]; ok == true {
		return v
	}


	ret := int64(1)

	for i := val; i >= 0; i -= 1 {
		ret += countDec(stelle + 1, i, mapDec)
	}

	mapDec[stelle][val] = ret
	
	return ret
}


func main() {

	mapInc := make(map[int]map[int]int64)
	mapDec := make(map[int]map[int]int64)

	for i := 0; i <= log; i += 1 {
		mapInc[i] = make(map[int]int64)
		mapDec[i] = make(map[int]int64)
	}

	inc := countInc(0, 0, mapInc)
	dec := countDec(0, 9, mapDec)

	fmt.Println(inc, dec, inc+dec - int64(9*log) - int64(2 + log))
}
