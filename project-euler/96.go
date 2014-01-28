package main

import (
	"fmt"
	"os"
)


func printSudoku(s [][]int) {
	for k, v := range s {
		fmt.Print(v[0], " ")
		fmt.Print(v[1], " ")
		fmt.Print(v[2], "|")

		fmt.Print(v[3], " ")
		fmt.Print(v[4], " ")
		fmt.Print(v[5], "|")

		fmt.Print(v[6], " ")
		fmt.Print(v[7], " ")
		fmt.Println(v[8])

		if (k-2) % 3 == 0 {
			fmt.Println("----- ----- -----")
		}
	}
	fmt.Println()
}


func copySudoku(s [][]int) [][]int {

	ret := make([][]int, 9)

	for k, v := range s {
		ret[k] = make([]int,9)

		for k2, v2 := range v {
			ret[k][k2] = v2
		}

	}

	return ret
}


func check(s [][]int, zero bool) string {

	zeroCount := 0
	
	for i := 0; i < 9; i += 1 {
		used := make(map[int]int)
		for j := 0; j < 9; j += 1 {
			if s[i][j] == 0 {
				zeroCount += 1
			}
			used[s[i][j]] += 1
		}
		if len(used) != 9-used[0] {
			return fmt.Sprint("wrong line ", i+1)
		}
	}

	for j := 0; j < 9; j += 1 {
		used := make(map[int]int)
		for i := 0; i < 9; i += 1 {
			used[s[i][j]] += 1
		}
		if len(used) != 9-used[0] {
			return fmt.Sprint("wrong column ", j+1)
		}
	}

	for i := 0; i < 9; i += 3 {
		for j := 0; j < 9; j += 3 {

			used := make(map[int]int)

			used[s[i][j]] += 1
			used[s[i][j+1]] += 1
			used[s[i][j+2]] += 1

			used[s[i+1][j]] += 1
			used[s[i+1][j+1]] += 1
			used[s[i+1][j+2]] += 1

			used[s[i+2][j]] += 1
			used[s[i+2][j+1]] += 1
			used[s[i+2][j+2]] += 1

			if len(used) != 9-used[0] {
				return fmt.Sprint("wrong block ", i+1, " ", j+1)
			}

		}
	}

	if zero == true {
		return ""
	} else if zeroCount > 0 {
		return "still zeros in there"
	}

	return ""

}


func copySudoku2(s, t [][]int) {
	for i, v := range t {
		for j, k := range v {
			s[i][j] = k
		}
	}
}


// ret success
func solve(s [][]int) bool {

	forbidden := [9][9][10]bool{}

	for {

		for i := 0; i < 9; i += 1 {
			for j := 0; j < 9; j += 1 {

				if s[i][j] != 0 {
					continue
				}

				for a := 0; a < 9; a += 1 {
					if a == i {
						continue
					}
					forbidden[i][j][s[a][j]] = true
				}


				for b := 0; b < 9; b += 1 {
					if b == j {
						continue
					}
					forbidden[i][j][s[i][b]] = true
				}


				ii, jj := 0, 0
				if i >= 6 { ii = 6
				} else if i >= 3 { ii = 3
				} else { ii = 0 }
				if j >= 6 { jj = 6
				} else if j >= 3 { jj = 3
				} else { jj = 0 }

				forbidden[i][j][s[ii][jj]] = true
				forbidden[i][j][s[ii][jj+1]] = true
				forbidden[i][j][s[ii][jj+2]] = true

				forbidden[i][j][s[ii+1][jj]] = true
				forbidden[i][j][s[ii+1][jj+1]] = true
				forbidden[i][j][s[ii+1][jj+2]] = true

				forbidden[i][j][s[ii+2][jj]] = true
				forbidden[i][j][s[ii+2][jj+1]] = true
				forbidden[i][j][s[ii+2][jj+2]] = true
			}
		}


		bestI, bestJ, bestForbiddenCount := 0, 0, 0

		progress := false

		done := 0

		for i := 0; i < 9; i += 1 {
			for j := 0; j < 9; j += 1 {

				if s[i][j] != 0 {
					done += 1
					continue
				}

				forbiddenCount := 0
				notForbidden := 0
				for k, v := range forbidden[i][j] {
					if k != 0 && v == true {
						forbiddenCount += 1
					} else if k != 0 {
						notForbidden = k
					}
				}

				if forbiddenCount == 8 {
					s[i][j] = notForbidden
					progress = true
					//fmt.Print("[",i+1, j+1,"] = ", notForbidden,"\n")
					//printSudoku(s)

					error := check(s, true)
					if error != "" {
						///fmt.Println(error)
					} else {
						///fmt.Println("success")
					}

				} else if forbiddenCount == 9 {
					//panic(fmt.Sprint("mistake at ", i, j))
					return false
				}

				if forbiddenCount > bestForbiddenCount {
					bestForbiddenCount = forbiddenCount
					bestI = i
					bestJ = j
				}
			}
		}


		if done == 81 {
			error := check(s, false)
			if error == "" {
				return true
			} else {
				///fmt.Println(error)
				return false
			}
		}

		//fmt.Println(bestI+1,bestJ+1,progress)


		if progress == false {

			i, j := bestI, bestJ

			//fmt.Println(bestForbiddenCount)

			for k, v := range forbidden[i][j] {

				if v == true || k == 0 {
					continue
				}


				sCopy := copySudoku(s)
				sCopy[i][j] = k

				///fmt.Print("fork [",i+1, j+1,"] = ", k,"\n")

				//printSudoku(sCopy)

				if solve(sCopy) == true {
					progress = true


					copySudoku2(s,sCopy)

					///fmt.Println("join success", check(s, false))

					//printSudoku(sCopy)

					break
				} else {

					forbidden[i][j][k] = true
					progress = true

					///fmt.Println("join fail", check(s, true))

				}
			//fmt.Println(bestForbiddenCount)

			}
		}

		//fmt.Println(bestI+1,bestJ+1,progress)

		if progress == false {
			panic("w00t")
		}
	}

	return false
}


func main() {

	file, error := os.Open("96.txt", os.O_RDONLY, 0666)
	defer file.Close()
	if error != nil {
		panic("cannot open input file \"96.txt\"")
	}

	sum := 0

	sudoku := make([][]int,9)
	for k, _ := range sudoku {
		sudoku[k] = make([]int,9)
	}

	for grid, i := 1, 0;; i += 1 {

		i = i % 9

		var line string
	
		_, error := fmt.Fscanln(file,&line)

		if error != nil {
			break
		}

		if len(line) != 9 {
			panic("line length != 9 w00t")
		}

		for k, v := range line {
			sudoku[i][k] = v-'0'
		}

		if i == 8 { // one soduko read

			//if grid == 3 {

			fmt.Println(grid)
			//printSudoku(sudoku)

			solve(sudoku)

			sum += sudoku[0][0]*100+sudoku[0][1]*10+sudoku[0][2]

			printSudoku(sudoku)

			error := check(sudoku, false)
			if error != "" {
				panic(error)
			}


			//}
			grid += 1


		}

	}

	fmt.Println(sum)

}

