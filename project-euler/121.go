package main

import (
	"big"
	"fmt"
)


func split(turn, maxTurns int, blueDiscsDrawn int, current, result *big.Rat) {

	if blueDiscsDrawn > (maxTurns / 2) {
		result.Add(result, current)
		//fmt.Println(blueDiscsDrawn, current)
		return
	} else if turn > maxTurns {
		return
	}

	redCurrent := big.NewRat(1,1)
	blueCurrent := big.NewRat(1,1)

	redCurrent.Mul(current, big.NewRat(int64(turn),int64(turn+1)))
	blueCurrent.Mul(current, big.NewRat(1,int64(turn+1)))

	split(turn+1, maxTurns, blueDiscsDrawn, redCurrent, result)
	split(turn+1, maxTurns, blueDiscsDrawn + 1, blueCurrent, result)


}


func main() {

	current := big.NewRat(1,1)
	result := big.NewRat(0,1)

	for rounds := 1; rounds <= 15; rounds += 1 {

		result.SetFrac64(0,1)

		split(1, rounds, 0, current, result)
		fmt.Println(result)
	}
}

