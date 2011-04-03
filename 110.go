package main


import (
	"fmt"
	"container/vector"
	"big"
)


func recursive(in int64, value *big.Int, v vector.IntVector, primeIndex int, primes []*big.Int, winner *big.Int, winner2 *vector.IntVector) {
	
	if in > 4000000 {

		if value.Cmp(winner) < 0 || winner.Cmp(big.NewInt(-1)) == 0 {
			winner.Set(value)
			*winner2 = v
			fmt.Println(in, winner, *winner2,)
			//fmt.Print(in, winner, *winner2, " (")
			//for k, v := range *winner2 {
			//	fmt.Print(primes[k], "**", v, " * ")
			//}
			//fmt.Println(")")
		}

		return
	}


	for i := int64(15); i >= 1; i -= 1 {

		var factor big.Int
		
		factor.Exp(primes[primeIndex], big.NewInt(i), nil)

		//fmt.Println(factor, i, primes[primeIndex])

		newV := v.Copy()
		newV.Push(int(i))

		var newValue big.Int
		newValue.Mul(value, &factor)


		recursive(in * (2*i+1) - i, &newValue, newV, primeIndex+1, primes, winner, winner2)

	}
}


func main() {

	primes := []*big.Int{
			big.NewInt(2),
			big.NewInt(3),
			big.NewInt(5),
			big.NewInt(7),
			big.NewInt(11),
			big.NewInt(13),
			big.NewInt(17),
			big.NewInt(19),
			big.NewInt(23),
			big.NewInt(29),
			big.NewInt(31),
			big.NewInt(37),
			big.NewInt(41),
			big.NewInt(43),
			big.NewInt(47),
			big.NewInt(53),
			big.NewInt(59),
			big.NewInt(61),
			big.NewInt(67),
			big.NewInt(71),
			big.NewInt(73),
			big.NewInt(79),
			big.NewInt(83),
			big.NewInt(89),
			big.NewInt(97)}

	winner := big.NewInt(-1)
	var winner2 vector.IntVector

	var v vector.IntVector
	
	recursive(1, big.NewInt(1), v, 0, primes, winner, &winner2)

	fmt.Println(winner)
}
