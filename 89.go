package main

import (
	"fmt"
	"container/vector"
	"os"
)


func generateGlyphMap() map[byte]int {
	ret := make(map[byte]int)
	ret['I'] = 1
	ret['V'] = 5
	ret['X'] = 10
	ret['L'] = 50
	ret['C'] = 100
	ret['D'] = 500
	ret['M'] = 1000
	return ret
}


func main() {

	differenceSum := 0

	glyphToNumber := generateGlyphMap()

	file, error := os.Open("89.txt", os.O_RDONLY, 0666)
	defer file.Close()

	if error != nil {
		panic("cannot open input file \"89.txt\"")
	}

	var numerals vector.StringVector

	var numeral string
	for {
		n, error := fmt.Fscanln(file,&numeral)
		if n == 0 || error != nil {
			break
		}
		numerals.Push(numeral)
	}

	for _, numeral := range numerals {

		number := 0

		currentGreatestGlyph := glyphToNumber[numeral[len(numeral)-1]]
		for i := len(numeral)-1; i >= 0; i -= 1 {

			glyph := numeral[i]

			if glyphToNumber[glyph] >= currentGreatestGlyph {
				number += glyphToNumber[glyph]
				currentGreatestGlyph = glyphToNumber[glyph]
			} else {
				number -= glyphToNumber[glyph]
			}

		}



		n := number


		minimalNumeral := ""

		// the commented regions are not allowed
		// i realized by trial and error

		for n >= 1000 {
			minimalNumeral += "M"
			n -= 1000
		}

		if n >= 900 {
			minimalNumeral += "CM"
			n -= 900
		//} else if n >= 800 {
		//	minimalNumeral += "CCM"
		//	n -= 800
		} else if n >= 500 {
			minimalNumeral += "D"
			n -= 500
		}

		if n >= 400 {
			minimalNumeral += "CD"
			n -= 400
		}

		for n >= 100 {
			minimalNumeral += "C"
			n -= 100
		}

		if n >= 90 {
			minimalNumeral += "XC"
			n -= 90
		// } else if n >= 80 {
		// 	minimalNumeral += "XXC"
		// 	n -= 80
		} else if n >= 50 {
			minimalNumeral += "L"
			n -= 50
		}

		if n >= 40 {
			minimalNumeral += "XL"
			n -= 40
		}

		for n >= 10 {
			minimalNumeral += "X"
			n -= 10
		}

		if n == 9 {
			minimalNumeral += "IX"
			n -= 9
		// } else if n == 8 {
		// 	minimalNumeral += "IIX"
		// 	n -= 8
		} else if n >= 5 {
			minimalNumeral += "V"
			n -= 5
		} else if n >= 4 {
			minimalNumeral += "IV"
			n -= 4
		}

		for n > 0 {
			minimalNumeral += "I"
			n -= 1
		}


		lengthDifference := len(numeral) - len(minimalNumeral)


		differenceSum += lengthDifference



		fmt.Println(numeral, number, minimalNumeral, lengthDifference)

		if lengthDifference < 0 {
			panic("w00t")
		}

	}

	fmt.Println(differenceSum)

}

