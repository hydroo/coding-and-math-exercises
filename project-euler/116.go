package main

import (
	"fmt"
)


func recursive(pos, n, m int/*, s string*/) int64 {
//func recursive(pos, n, m int, hasBlack bool, s string) int64 {

	count := int64(0)

	if pos <= n {

		count += recursive(pos + 1, n, m/*, s + "b"*/)
		//count += recursive(pos + 1, n, m, true, s + "b")

		if pos + m - 2 < n {

			count += recursive(pos + m, n, m/*, s*/)
			//count += recursive(pos + m, n, m, s)

		} else if pos + m - 1 == n {

			//fmt.Println(s)
			count += 1

		}

	} else if pos > n {

		//fmt.Println(s)
		count += 1

	}
	

	return count
}


func main() {

	n := 49

	count := int64(0)

	for m := 2; m <= 4; m += 1 {

		c := recursive(0, n, m/*, ""*/) - 1
		//c := recursive(0, n, m, "") - 1

		fmt.Println(n+1, m, c)

		count += c
	}

	fmt.Println(count)
}

