package main

import (
	"fmt"
	"sort"
)


type asdf struct {
	a, b map[int]bool
}


func check(a,b map[int]bool) bool {

	has01 := false
	has04 := false
	has09 := false
	has16 := false
	has25 := false
	has36 := false
	has49 := false
	has64 := false
	has81 := false

	_, a0 := a[0]
	_, a1 := a[1]
	_, a2 := a[2]
	_, a3 := a[3]
	_, a4 := a[4]
	_, a5 := a[5]
	_, a6 := a[6]
	_, a8 := a[8]
	_, a9 := a[9]
	_, b0 := b[0]
	_, b1 := b[1]
	_, b2 := b[2]
	_, b3 := b[3]
	_, b4 := b[4]
	_, b5 := b[5]
	_, b6 := b[6]
	_, b8 := b[8]
	_, b9 := b[9]

	if (a0 && b1) || (b0 && a1) {
		has01 = true
	}
	if (a0 && b4) || (b0 && a4) {
		has04 = true
	}
	if (a0 && b9) || (b0 && a9) || (a0 && b6) || (b0 && a6) {
		has09 = true
	}
	if (a1 && b6) || (b1 && a6) || (a1 && b9) || (b1 && a9) {
		has16 = true
	}
	if (a2 && b5) || (b2 && a5) {
		has25 = true
	}
	if (a3 && b6) || (b3 && a6) || (a3 && b9) || (b3 && a9) {
		has36 = true
	}
	if (a4 && b9) || (b4 && a9) || (a4 && b6) || (b4 && a6) {
		has49 = true
	}
	if (a6 && b4) || (b6 && a4) || (a9 && b4) || (b9 && a4) {
		has64 = true
	}
	if (a8 && b1) || (b8 && a1) {
		has81 = true
	}

	return has01 && has04 && has09 && has16 && has25 && has36 && has49 && has64 && has81

}


func recursive(a, b map[int]bool, lastA, lastB int, results map[string]bool) {

	if len(a) < 6 {

		for i := lastA+1; i < 10; i += 1 {

			if _, ok := a[i]; ok == true {
				continue
			} else {
				tmpA := make(map[int]bool)
				for k, v := range a {
					tmpA[k] = v
				}
				tmpA[i] = true

				recursive(tmpA, b, i, lastB, results)
			}
		}

	}

	
	if len(b) < 6 {

		for i := lastB+1; i < 10; i += 1 {

			if _, ok := b[i]; ok == true {
				continue
			} else {
				tmpB := make(map[int]bool)
				for k, v := range b {
					tmpB[k] = v
				}
				tmpB[i] = true

				recursive(a, tmpB, lastA, i, results)
			}

		}

	}


	if len(a) == 6 && len(b) == 6 {

		if check(a, b) {

			str1, str2 := "", ""

			for k, _ := range a {
				str1 += fmt.Sprint(k)
			}
			for k, _ := range b {
				str2 += fmt.Sprint(k)
			}

			_, ok1 := results[str1+str2]
			_, ok2 := results[str2+str1]

			if ok1 == false && ok2 == false{

				results[str1+str2] = true

				str2 := ""

				vectorA := make([]int,6)
				i := 0
				for k, _ := range a {
					vectorA[i] = k
					i += 1
				}

				vectorB := make([]int,6)
				j := 0
				for k, _ := range b {
					vectorB[j] = k
					j += 1
				}

				sort.SortInts(vectorA)
				sort.SortInts(vectorB)

				for _, v := range vectorA {
					str2 += fmt.Sprint(v)
				}

				str2 += ","
				for _, v := range vectorB {
					str2 += fmt.Sprint(v)
				}

				fmt.Println(str2, len(results))
			}


		}
	}

}


func main() {
	fmt.Println()

	a := make(map[int]bool)
	b := make(map[int]bool)

	results := make(map[string]bool)

	recursive(a,b, -1, -1, results)

}

