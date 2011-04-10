package main

import (
	"fmt"
)


func recursiv(pos, max int/*, current string*/) int64 {

	count := int64(0)

	if pos <= max {

		count += recursiv(pos + 1, max/*, current + "b"*/)

		//current += "rr"

		for length := 3; ; length += 1 {

			//current += "r"

			if pos + length - 1 < max {

				count += recursiv(pos + length + 1, max/*, current + "b"*/)

			} else if pos + length - 1 == max {

				//fmt.Println(current)
				count += 1

			} else {
				break
			}
		}

	} else if pos > max {

		//fmt.Println(current)
		count += 1

	}
	
	return count
}


func main() {

	min := 0
	max := 49

	count := recursiv(min, max/*, ""*/)

	fmt.Println(count)
}

