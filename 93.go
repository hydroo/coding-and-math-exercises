package main

import (
	"fmt"
)


// [24][4]int
func permutationsOfDigits(a,b,c,d int) [][]int {
	results := make([][]int,24)
	nextResultIndex := 0

	abcd := make([]int,4)
	abcd[0] = a
	abcd[1] = b
	abcd[2] = c
	abcd[3] = d

	free := map[int]bool{a:true,b:true,c:true,d:true}

	permutationsOfDigitsRecursive(free,abcd,0,results,&nextResultIndex)

	return results
}
func permutationsOfDigitsRecursive(free map[int]bool, nextPermutation []int, currentIndex int, results [][]int, nextResultIndex *int) {

	if currentIndex == 4 {
		results[*nextResultIndex] = nextPermutation
		*nextResultIndex += 1
		return
	}

	for k, v := range free {
		if v == false {
			continue
		}

		nextPermutationCopy := make([]int,4)
		copy(nextPermutationCopy,nextPermutation)
		nextPermutationCopy[currentIndex] = k

		freeCopy := make(map[int]bool)
		for k2, v2 := range free {
			freeCopy[k2] = v2
		}
		freeCopy[k] = false

		permutationsOfDigitsRecursive(freeCopy,nextPermutationCopy,currentIndex+1,results,nextResultIndex)
	}

}


// [64][3]int
func createAllOperatorCombinations() [][]int {
	results := make([][]int,64)
	nextResultIndex := 0
	nextCombination := make([]int,3)
	createAllOperatorCombinationsRecursive(nextCombination,0,results, &nextResultIndex)
	return results
}
func createAllOperatorCombinationsRecursive(nextCombination []int, currentIndex int, results [][]int, nextResultIndex *int) {

	if currentIndex == 3 {
		results[*nextResultIndex] = nextCombination
		*nextResultIndex += 1
		return
	}

	for i := 0; i < 4; i += 1 {
		nextCombinationCopy := make([]int,3)
		copy(nextCombinationCopy,nextCombination)
		nextCombinationCopy[currentIndex] = i

		createAllOperatorCombinationsRecursive(nextCombinationCopy,currentIndex+1,results,nextResultIndex)
	}
}


func calculate(aa,bb,cc,dd int, operators []int, results map[int]bool) {

	a := float64(aa)
	b := float64(bb)
	c := float64(cc)
	d := float64(dd)

	o0 := operators[0]
	o1 := operators[1]
	o2 := operators[2]


	//((xx)x)x
	res0 := X(X(X(a,b,o0),c,o1),d,o2)
	if res0 == float64(int(res0)) {
		results[int(res0)] = true
	}

	//(x(xx))x
	res1 := X(X(a,X(b,c,o1),o0),d,o2)
	if res1 == float64(int(res1)) {
		results[int(res1)] = true
	}

	//x((xx)x)
	res2 := X(a,X(X(b,c,o1),d,o2),o0)
	if res2 == float64(int(res2)) {
		results[int(res2)] = true
	}

	//x(x(xx))
	res3 := X(a,X(b,X(c,d,o2),o1),o0)
	if res3 == float64(int(res3)) {
		results[int(res3)] = true
	}

	//(xx)(xx)
	res4 := X(X(a,b,o0),X(c,d,o2),o1)
	if res4 == float64(int(res4)) {
		results[int(res4)] = true
	}



}
func X(a,b float64, operator int) float64 {
	ret := 0.0
	switch operator {
		case 0: ret = a + b
		case 1: ret = a - b
		case 2: ret = a * b
		case 3: ret = a / b
		default : panic("w00t")
	}
	return ret
}


func main() {

	min := 0
	max := 9

	operators := createAllOperatorCombinations()
	permutations := permutationsOfDigits(0,1,2,3)

	bestAbcd := ""
	bestN := 0

	results := make(map[string]int)

	abcd := make([]int,4)


	for abcd[0] = min; abcd[0] <= max; abcd[0] += 1 {
		for abcd[1] = abcd[0]+1; abcd[1] <= max; abcd[1] += 1 {
			for abcd[2] = abcd[1]+1; abcd[2] <= max; abcd[2] += 1 {
				for abcd[3] = abcd[2]+1; abcd[3] <= max; abcd[3] += 1 {

					availableResults := make(map[int]bool)

					for _, perm := range permutations {

						for _, operatorCombination := range operators {

							calculate(abcd[perm[0]],
									abcd[perm[1]],
									abcd[perm[2]],
									abcd[perm[3]],
									operatorCombination,
									availableResults)

						}

					}

					to := 0
					for i := 1; ; i += 1 {
						if availableResults[i] == false {
							to = i-1
							break
						}
					}

					if to >= bestN {
						bestAbcd = fmt.Sprint(abcd)
						bestN = to

						results[bestAbcd] = bestN

						fmt.Println(bestN, abcd)
					} else {
						//fmt.Println(to, abcd)
					}
				}
			}
		}
	}

	/*fmt.Println()
	for k, v := range results {
		fmt.Println(v, k)
	}*/
	fmt.Println("==",bestAbcd, bestN)

}

