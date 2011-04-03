package main

import (
	"fmt"
	"math"
)


func main() {

	maxmaxCubeSiteLength := int64(1816)

	for maxCubeSiteLength := int64(maxmaxCubeSiteLength);maxCubeSiteLength <= int64(maxmaxCubeSiteLength); maxCubeSiteLength += 1 {

		fmt.Print("")

		squares := make(map[int64]bool)
		maxSquare := int64(0)

		counter := 0

		/* create the map of squares */
		for i := int64(0); i <= int64(math.Pow(float64(maxCubeSiteLength),2))*3; i += 1 {
			maxSquare = i*i
			squares[maxSquare] = true
		}


		/* iterate over all cuboids */
		for x := int64(1); x <= maxCubeSiteLength; x+=1 {
			for y := x; y <= maxCubeSiteLength; y+=1 {
				for z := y; z <= maxCubeSiteLength; z+=1 {
					
					lengthSquared := z*z + (x+y)*(x+y)

					if lengthSquared > maxSquare {
						panic("max square is not big enough")
					}

					_, ok := squares[lengthSquared]

					if ok == true {
						counter += 1
						//fmt.Println(x,y,z,":",math.Sqrt(float64(lengthSquared)), "cntr", counter)

						if counter % 10000 == 0 {
							fmt.Println(maxCubeSiteLength,x,y,z,"cntr",counter)
						}

						if counter == 1000000 {
							fmt.Println("!!!!!!!!!!!!!",x,y,z,"!!!!!!!!!!!!!!!!")
						}
					}
				}
			}
		}

		fmt.Println(maxCubeSiteLength,"cntr",counter)

	}
}

