package main

import (
	"fmt"
	"math"
	"os"
)

type point struct {
	x,y float64
}

type triangle struct {
	a, b, c point
}


func (t triangle) Print() string {
	return fmt.Sprint("([",t.a.x,t.a.y,"][",t.b.x,t.b.y,"][",t.c.x,t.c.y,"])")
}


func readFile() []triangle {

	file, error := os.Open("102.txt", os.O_RDONLY, 0666)
	if error != nil {
		panic("cannot open input file \"96.txt\"")
	}
	defer file.Close()

	ret := make([]triangle, 1000)

	for i := 0;i < 1000; i += 1 {

		read, error := fmt.Fscanln(file,
				&(ret[i].a.x), &(ret[i].a.y),
				&(ret[i].b.x), &(ret[i].b.y),
				&(ret[i].c.x), &(ret[i].c.y))
		if read == 0 || error != nil {
			fmt.Println(i)
			panic(error)
			break
		}

	}

	return ret
}


func dotProduct(a,b point) float64 {
	return a.x*b.x + a.y*b.y
}


func normalize(a point) point {
	l := math.Sqrt(a.x*a.x+a.y*a.y)
	return point{a.x/l, a.y/l}
}


func check(t triangle) bool {

	t.a = normalize(t.a)
	t.b = normalize(t.b)
	t.c = normalize(t.c)

	dp1 := dotProduct(t.a,t.b)
	dp2 := dotProduct(t.b,t.c)
	dp3 := dotProduct(t.c,t.a)

	angle1 := math.Acos(dp1)
	angle2 := math.Acos(dp2)
	angle3 := math.Acos(dp3)

	fmt.Println(dp1, dp2, dp3, dp1+dp2+dp3)
	fmt.Println(angle1, angle2, angle3, angle1+angle2+angle3)

	return angle1+angle2+angle3 >= 6.28318530

}

func main() {

	triangles := readFile()

	count := 0

	for k, t := range triangles {

		if check(t) == true {
			count += 1
			fmt.Println(k, t.Print(),"+++\n")
		} else {
			fmt.Println(k, t.Print(),"---\n")
		}

		if k == 1 {
			//break
		}
	}


	fmt.Println(count)

}

