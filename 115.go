package main

import (
	"fmt"
)


func recursive(pos, n, m int) int64 {

	count := int64(0)

	if pos <= n {

		count += recursive(pos + 1, n, m)

		for length := m; ; length += 1 {

			if pos + length - 1 < n {

				count += recursive(pos + length + 1, n, m)

			} else if pos + length - 1 == n {

				count += 1

			} else {
				break
			}
		}

	} else if pos > n {

		count += 1

	}
	
	return count
}


func main() {

	n := 167
	m := 50

	count := recursive(0, n, m)

	fmt.Println(count)
}

