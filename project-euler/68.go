package main

import (
	"fmt"
)


func permutationsGenerator(resultChannel chan<- [10]int) {

	freeElements := map[int]bool{
		1: true, 2: true, 3: true, 4: true, 5: true,
		6: true, 7: true, 8: true, 9: true, 10: true,
	}

	recursivePermutations([10]int{}, 0, freeElements, resultChannel)
}


func recursivePermutations(result [10]int, pos int, freeElements map[int]bool, resultChannel chan<- [10]int) {

	// fmt.Println(result, freeElements)

	if pos == 10 {
		resultChannel <- result
		return
	}

	for i := 1; i < 11; i++ {

		// fmt.Println(i, freeElements[i])

		if freeElements[i] == true {

			result[pos] = i

			freeElements[i] = false
			recursivePermutations(result, pos+1, freeElements, resultChannel)
			freeElements[i] = true
		}

	}
}


func makeFiveGon(permutation [10]int) [5][3]int {

	var fiveGon [5][3]int

	fiveGon[0][0] = permutation[0]
	fiveGon[0][1] = permutation[5]
	fiveGon[0][2] = permutation[6]

	fiveGon[1][0] = permutation[1]
	fiveGon[1][1] = permutation[6]
	fiveGon[1][2] = permutation[7]

	fiveGon[2][0] = permutation[2]
	fiveGon[2][1] = permutation[7]
	fiveGon[2][2] = permutation[8]

	fiveGon[3][0] = permutation[3]
	fiveGon[3][1] = permutation[8]
	fiveGon[3][2] = permutation[9]

	fiveGon[4][0] = permutation[4]
	fiveGon[4][1] = permutation[9]
	fiveGon[4][2] = permutation[5]

	return fiveGon
}


func isTenOnOuterRing(permutation [10]int) bool {
	return permutation[0] == 10 ||
		permutation[1] == 10 ||
		permutation[2] == 10 ||
		permutation[3] == 10 ||
		permutation[4] == 10
}


func sumsAreAllEqual(fiveGon [5][3]int) bool {

	a := fiveGon

	sum := a[0][0] + a[0][1] + a[0][2]

	return a[1][0]+a[1][1]+a[1][2] == sum &&
		a[2][0]+a[2][1]+a[2][2] == sum &&
		a[3][0]+a[3][1]+a[3][2] == sum &&
		a[4][0]+a[4][1]+a[4][2] == sum

}


func isSorted(fiveGon [5][3]int) bool {

	smallest := fiveGon[0][0]

	return smallest < fiveGon[1][0] &&
			smallest < fiveGon[2][0] &&
			smallest < fiveGon[3][0] &&
			smallest < fiveGon[4][0]
}


func main() {

	permutationsChannel := make(chan [10]int, 100)

	go permutationsGenerator(permutationsChannel)

	for {

		permutation := <-permutationsChannel

		if isTenOnOuterRing(permutation) == false {
			continue
		}

		fiveGon := makeFiveGon(permutation)

		if sumsAreAllEqual(fiveGon) == false {
			continue
		}

		if isSorted(fiveGon) == false {
			continue
		}

		fmt.Println(fiveGon)
	}

}
