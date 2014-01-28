package main

import (
	"fmt"
)


type checkout struct {
	first, second, third int;
	firstMultiplier, secondMultiplier int;
}


func newCheckout(first, second, third, firstMultiplier, secondMultiplier int) *checkout {
	var c checkout

	c.first = first
	c.second = second
	c.third = third
	c.firstMultiplier = firstMultiplier
	c.secondMultiplier = secondMultiplier

	return &c
}

func (c checkout) Score() int {
	return c.first*c.firstMultiplier + c.second*c.secondMultiplier + c.third*2
}


func (c checkout) Unique() string {

	var ret string

	switch c.firstMultiplier {
	case 0:
	case 1: ret += "S"
	ret += fmt.Sprintf("%d ", c.first)
	case 2: ret += "D"
	ret += fmt.Sprintf("%d ", c.first)
	case 3: ret += "T"
	ret += fmt.Sprintf("%d ", c.first)
	}


	switch c.secondMultiplier {
	case 0:
	case 1: ret += "S"
	ret += fmt.Sprintf("%d ", c.second)
	case 2: ret += "D"
	ret += fmt.Sprintf("%d ", c.second)
	case 3: ret += "T"
	ret += fmt.Sprintf("%d ", c.second)
	}



	ret += "D"
	ret += fmt.Sprintf("%d", c.third)


	return ret
}


func main() {

	eyes := []int{0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,25}
	multipliers := []int{1,2,3}

	checkouts := make(map[string]int)


	for _, third := range eyes {
	
		if third == 0 {
			continue
		}

		for _, second := range eyes {
			for _, secondMultiplier := range multipliers {

				if second == 0 {
					secondMultiplier = 0
				}

				if second == 25 && secondMultiplier == 3 {
					continue
				}

				for _, first := range eyes {
					for _, firstMultiplier := range multipliers {

						if first == 0 {
							firstMultiplier = 0
						}

						if first == 25 && firstMultiplier == 3 {
							continue
						}

						if first*firstMultiplier < second*secondMultiplier ||
							((first*firstMultiplier == second*secondMultiplier) &&
							(first < second)){
							continue
						}


						c := newCheckout(first,second,third,firstMultiplier,secondMultiplier)

						checkouts[c.Unique()] = c.Score()

					}
				}

			}
		}

	}

	count := 0

	for k, v := range checkouts {
	
		if v < 100 {
			count += 1

			fmt.Println(k, v)
		}

	}

	fmt.Println(len(checkouts), count)

}
