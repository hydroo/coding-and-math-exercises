package main

import (
	"fmt"
	//"math"
)

func main() {

	type K struct {
		mults int
		variants map[int][]int
	}


	max := 200

	ks := make([]K,max+1)

	for i, _ := range ks {
		ks[i].mults = 1000000000
		ks[i].variants = make(map[int][]int)
	}

	ks[1].mults = 0
	ks[1].variants[0] = make([]int,max+1)
	ks[1].variants[0][1] = 1


	sum := 0


	for k, _ := range ks {

		if k == 0 {
			continue
		}

		for l, _ := range ks {
			
			if l == 0 {
				continue
			}

			if l >= k {
				break
			}

			if ks[k].mults <= ks[l].mults {
				continue
			} else {

				for _, variant := range ks[l].variants {

					is := make(map[int]int)
					for i := 1; i <= max; i += 1 {
						if variant[i] == 1 {
							is[i] = 1
						}
					}

					for i := 1; i <= max; i += 1 {

						if variant[i] == 1 && l + i == k {

							if  ks[k].mults > ks[l].mults + 1 {
								ks[k].variants = make(map[int][]int)
							}

							ks[k].mults = ks[l].mults + 1

							newvariantindex := len(ks[k].variants)

							ks[k].variants[newvariantindex] = make([]int, max+1)

							for a, b := range variant {
								ks[k].variants[newvariantindex][a] = b
							}
							ks[k].variants[newvariantindex][k] = 1

							continue
						}

					}
				}


			}

		}

		sum += ks[k].mults

		fmt.Println(k,":", ks[k].mults)
		//for _, v := range ks[k].variants {
		//	itemcount := 0
		//	fmt.Print("  ")
		//	for w, x := range v {
		//		if x == 1 {
		//			itemcount += 1
		//			fmt. Print(w, " ")
		//		}
		//	}
		//	fmt.Print(":",itemcount-1,"\n")

		//	if itemcount - 1 != ks[k].mults {
		//		panic("")
		//	}
		//}

	}

	fmt.Println(sum)

}

