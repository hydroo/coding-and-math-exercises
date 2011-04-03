package main

import (
	"fmt"
	"os"
	"strings"
)


func readFile() [][]int {

	file, error := os.Open("107.txt", os.O_RDONLY, 0666)
	if error != nil {
		panic("cannot open input file \"107.txt\"")
	}
	defer file.Close()

	ret := make([][]int, 40)

	for i := 0; ; i += 1{
		
		var line string

		read, error := fmt.Fscanln(file, &line)
		if read == 0 || error != nil {
			break
		}

		cells := strings.Split(line, ",", -1)

		if len(cells) != 40 {
			panic("wrong number of cells")
		}

		ret[i] = make([]int, 40)

		for k, v := range cells {
			if v == "-" {
				ret[i][k] = -1
			} else {
				scanned, error := fmt.Sscan(v, &ret[i][k])
				if scanned == 0 || error != nil {
					panic(fmt.Sprint(i,k,v,error))
				}
			}
		}

	}

	return ret
}


func hasCircle(matrix [][]int) bool {

	for start := 0; start < 40; start += 1 {

		visited := make(map[int]bool)

		circleFound := recursiveWalk(matrix, start, -1, visited)

		if circleFound == true {
			return true
		}

	}

	return false
}


func recursiveWalk(matrix [][]int, current, previous int, visited map[int]bool) bool {

	if _, ok := visited[current]; ok == true {
		return true
	} else {
		visited[current] = true
	}


	for k, v := range matrix[current] {

		if v == -1 || k == previous {
			continue
		}

		visited2 := make(map[int]bool)
		for k, v := range visited {
			visited2[k] = v
		}

		circleFound := recursiveWalk(matrix, k, current, visited2)

		if circleFound == true {
			return true
		}

	}

	return false

}


func printMatrix(matrix [][]int) {
	fmt.Print("   ")
	for i := 0; i < 40; i += 1 {
		fmt.Printf("%4d", i)
	}
	fmt.Println()

	for k, v := range matrix {
		fmt.Printf("%2d ",k)

		for _, w := range v {
			if w == -1 {
				fmt.Print("   -")
			} else {
				fmt.Printf(" %3d", w)
			}
		}
		fmt.Println()
	}
}


func main() {

	matrix := readFile()

	completeWeight := 0

	for i := 0; i < 40; i += 1 {
		for j := 0; j < 40; j += 1 {
			
			if matrix[i][j] != -1 {
				completeWeight += matrix[i][j]
			}
		}
	}


	newWeight := 0
	edgeCount := 0

	matrix2 := make([][]int, 40)
	for k, _ := range matrix2 {
		matrix2[k] = make([]int, 40)
		for k2, _ := range matrix2[k] {
			matrix2[k][k2] = -1
		}
	}

	for {

		smallestEdgeFrom := -1
		smallestEdgeTo := -1
		smallestEdgeLength := -1

		for i := 0; i < 40; i += 1 {
			for j := 0; j < 40; j += 1 {

				if matrix[i][j] == -1 {
					continue
				}

				if matrix[i][j] < smallestEdgeLength || smallestEdgeLength == -1 {

					matrix2[i][j] = matrix[i][j]
					matrix2[j][i] = matrix[i][j]

					if hasCircle(matrix2) == false {

						smallestEdgeFrom = i
						smallestEdgeTo = j
						smallestEdgeLength = matrix[i][j]

					}

					matrix2[i][j] = -1
					matrix2[j][i] = -1

				}

			}
		}

		if smallestEdgeLength == -1 {
			break
		}

		matrix[smallestEdgeFrom][smallestEdgeTo] = -1
		matrix[smallestEdgeTo][smallestEdgeFrom] = -1

		matrix2[smallestEdgeFrom][smallestEdgeTo] = smallestEdgeLength
		matrix2[smallestEdgeTo][smallestEdgeFrom] = smallestEdgeLength

		newWeight += smallestEdgeLength

		//fmt.Println(smallestEdgeLength)

		edgeCount += 1

	}

	printMatrix(matrix)
	fmt.Println()
	printMatrix(matrix2)


	fmt.Println(completeWeight, newWeight, completeWeight - newWeight)

}


