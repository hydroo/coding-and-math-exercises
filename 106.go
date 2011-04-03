package main

import (
	"container/vector"
	"fmt"
	//"math"
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


func invert(c []int) []int {
	ret := make([]int, len(c))

	for k, v := range c {
		if v == 1 {
			ret[k] = 2
		} else if v == 2 {
			ret[k] = 1
		} else if v == 0 {
			ret[k] = 0
		}
	}

	return ret
}


func removeZeros(c []int) []int {
	var ret vector.IntVector
	for _, v := range c {
		if v != 0 {
			ret.Push(v)
		}
	}
	return ret
}


func sameSize(c []int) bool {
	a := 0
	for _, v := range c {
		if v == 1 {
			a -= 1
		} else if v == 2 {
			a += 1
		}
	}
	return a == 0
}


func evenlyDistributed(c []int) bool {
	current := 0
	n := 0

	for _, v := range c {
		if current == 0 && v == 1 {
			current = 1
			n = 1
		} else if current == 1 && v == 1 {
			n += 1
		} else if current == 1 && v == 2 {
			if n < 0 {
				return false
			}
			current = 2
			n -= 1
		} else if current == 2 && v == 2 {
			n -= 1
		} else if current == 2 && v == 1 {
			if n != 0 {
				return false
			}
			current = 1
			n = 1
		} else if v == 0 {
			/* ignore zeros */
		} else {
			return false
		}
	}

	return n == 0
}


//func magic(c []int) bool {
//
//	c2 := make([]int, len(c))
//	copy(c2, c)
//
//	var weight vector.IntVector
//
//	for {
//
//		firstOne := -1
//		lastOne := -1
//		firstTwo := -1
//		lastTwo := -1
//
//
//		for k, v := range c2 {
//
//			if v == 1 && firstOne == -1 {
//				firstOne = k
//			} else if v == 2 && firstTwo == -1 {
//				firstTwo = k
//			}
//			if v == 1 {
//				lastOne = k
//			} else if v == 2 {
//				lastTwo = k
//			}
//		}
//
//
//		//fmt.Println(firstOne, firstTwo, lastOne, lastTwo, weight)
//
//		if firstOne != -1 && (firstOne < firstTwo || firstTwo == -1) {
//			/* one in front */
//
//			if lastTwo > lastOne {
//				/* two in the back */
//
//				c2[firstOne] = 0
//				c2[lastTwo] = 0
//				weight.Push(2) /* more weight for 2 on the right */
//
//			} else if lastTwo < lastOne {
//				/* one in the back */
//
//				c2[firstOne] = 0
//				c2[lastOne] = 0
//				weight.Push(1) /* more weight for 1 on the right */
//
//			} else {
//				break
//			}
//
//		} else if firstTwo != -1 && (firstTwo < firstOne || firstOne == -1) {
//			/* two in front */
//
//			if lastOne < lastTwo {
//				/* two in the back */
//
//				c2[firstTwo] = 0
//				c2[lastTwo] = 0
//				weight.Push(2) /* more weight for 2 on the right */
//
//			} else if lastTwo < lastOne {
//				/* one in the back */
//
//				c2[firstTwo] = 0
//				c2[lastOne] = 0
//				weight.Push(1) /* more weight for 2 on the right */
//
//			} else {
//				break
//			}
//		} else {
//			break
//		}
//
//
//	}
//
//	//fmt.Println("  ", weight)
//
//	return weight[0] == weight[1]
//}


func magic(c []int) bool {

	c2 := make([]int, len(c))
	copy(c2, c)

	for k, v := range c2 {

		if v == 1 {

			i := k+1
			for ; i < len(c2); i += 1 {

				if c2[i] == 2 {
					c2[k] = 0
					c2[i] = 0
					break
				}

			}

			if i == len(c2) {
				return false
			}

		}

	}

	return true
}


func main() {

	combinations := indexCombinations(12)

	count := 0
	magicCount := 0

	done := make(map[string]bool)
	doneWithoutZeros := make(map[string]bool)


	for k, combination := range combinations {
		
		/* handle inverted sets */
		combinationInverted := invert(combination)

		combinationInvertedString := fmt.Sprint(combinationInverted)

		if _, ok := done[combinationInvertedString]; ok == true {
			continue
		} else {
			combinationString := fmt.Sprint(combination)
			done[combinationString] = true
			done[combinationInvertedString] = true
		}

		/* rule out sets with different sizes */
		if sameSize(combination) == false {
			continue
		}

		if evenlyDistributed(combination) == true {
			continue
		}

		appendix := ""

		if magic(combination) == true {
			appendix = "---"
			magicCount += 1
		}

		combinationWithoutZeros := removeZeros(combination)

		if _, ok := doneWithoutZeros[fmt.Sprint(combinationWithoutZeros)]; ok == false {
			fmt.Println(k, combinationWithoutZeros, appendix, "\n")

			doneWithoutZeros[fmt.Sprint(combinationWithoutZeros)] = true
		}

		count += 1

	}

	// TODO 

	fmt.Println(count, magicCount, len(combinations)/2)
	
}


