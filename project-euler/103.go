package main

import (
	"fmt"
)


func setSum(a []int) int {
	ret := 0
	for _, v := range a {
		ret += v
	}
	return ret
}


//0 = nowhere, 1 = first set, 2 = second set
func indexCombinations(n int) [][]int {
	resultMap := make(map[int][]int)
	nextResultMapKey := 0
	firstCombination := make([]int, n)

	indexCombinationsRecursive(n, firstCombination, 0, resultMap, &nextResultMapKey)

	ret := make([][]int, len(resultMap))
	for k, v := range resultMap {
		ret[k] = v
	}

	return ret
}
func indexCombinationsRecursive(n int, combination []int, currentIndex int, results map[int][]int, nextResultMapKey *int) {
	if currentIndex == n {

		has1 := false
		has2 := false

		for _, v := range combination {
			if v == 1 {
				has1 = true
			} else if v == 2 {
				has2 = true
			}
		}

		if has1 == true && has2 == true {
			results[*nextResultMapKey] = combination
			*nextResultMapKey += 1
		}

		return
	}

	for i := 0; i <= 2; i += 1 {
		combinationCopy := make([]int,len(combination))
		copy(combinationCopy, combination)
		combinationCopy[currentIndex] = i

		indexCombinationsRecursive(n, combinationCopy, currentIndex + 1, results, nextResultMapKey)
	}
}


func setSumsDifferent(s []int, combinations [][]int) bool {

	for _, combination := range combinations {

		sum1 := 0
		sum2 := 0

		c1 := 0
		c2 := 0

		for k, v := range combination {

			if v == 1 {
				c1 += 1
				sum1 += s[k]
			} else if v == 2{
				c2 += 1
				sum2 += s[k]
			}

		}

		if (c1 == c2 && sum1 == sum2) ||
				(c1 > c2 && sum1 <= sum2) ||
				(c1 < c2 && sum1 >= sum2) {
			return false
		}

	}

	return true
}


func findMinimumSet(s []int, combinations [][]int) []int {
	ret := make([]int, len(s))
	copy(ret, s)
	progress := int64(0)
	resultSum := setSum(ret)

	findMinimumSetRecursive(s, 0, combinations, ret, &resultSum, &progress)

	return ret
}
func findMinimumSetRecursive(s []int, currentIndex int, combinations [][]int, result []int, resultSum *int, progress *int64) {
	
	if currentIndex == len(s) {

		sum := setSum(s)

		if sum < *resultSum && setSumsDifferent(s, combinations) == true {
			copy(result,s)
			*resultSum = sum
			fmt.Println("w00t nice", result)
		}

		*progress += 1

		if *progress == 1 || *progress % 5000000 == 0 {
			fmt.Println(s, *progress)
		}

		return
		
	}


	min := s[currentIndex]-40
	if currentIndex > 0 {
		if min <= s[currentIndex-1] {
			min = s[currentIndex-1]+1
		}
	} else {
		if min < 0 {
			min = 0
		}
	}


	for i := min; i <= s[currentIndex]+60; i += 1 {
		sCopy := make([]int, len(s))
		copy(sCopy,s)

		sCopy[currentIndex] = i

		findMinimumSetRecursive(sCopy, currentIndex+1, combinations, result, resultSum, progress)
	}
}


func main() {

	//base := []int{19,30,37,38,39,41,44}
	//base := []int{11,18,19,20,22,25}
	//base := []int{11,17,20,22,23,24}
	base := []int{20,31,38,39,40,42,45}

	combinations := indexCombinations(len(base))

	minimum := findMinimumSet(base, combinations)
	fmt.Println(minimum, setSum(minimum))
	
}

