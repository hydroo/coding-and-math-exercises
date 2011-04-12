package main

import (
	"big"
	"fmt"
)


var zero *big.Int
var one *big.Int


func recursive(pos, n int, current string, memory map[int]*big.Int, result *big.Int) {

	if pos < n + 1 {

		if v, ok := memory[pos]; ok == true {
			result.Add(result, v)
			return
		}

		recursive(pos + 1, n, current + "1", memory, result)

		if pos + 2 - 2 < n {

			recursive(pos + 2, n, current + "2", memory, result)
		}

		if pos + 3 - 2 < n {

			recursive(pos + 3, n, current + "3", memory, result)
		}

		if pos + 4 - 2 < n {

			recursive(pos + 4, n, current + "4", memory, result)
		}

	} else if pos > n + 1 {

		result.Add(result, zero)
	
	} else if pos == n + 1 {

		//fmt.Println(current)
		result.Add(result, one)

	}
}


func main() {

	zero = big.NewInt(0)
	one = big.NewInt(1)


	n := 50

	memory := make(map[int]*big.Int)

	for i := n-1; i >= 1; i -= 1 {

		result := big.NewInt(0)

		recursive(i, n, "", memory, result)

		memory[i] = result

		fmt.Println(i, memory[i])
	}


	fmt.Println("\n", memory[1])
}

