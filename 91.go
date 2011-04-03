package main

import (
	"fmt"
)


type point struct {
	x, y int
}


func (p point) Hash() string {
	return fmt.Sprint(p.x, p.y)
}


func (p point) Equals(q point) bool {
	return p.x == q.x && p.y == q.y
}


type triangle struct {
	a, b, c point
}


func (t *triangle) Sort() {


	if t.a.x > t.b.x {
		tmp := t.a
		t.a = t.b
		t.b = tmp
	}

	if t.b.x > t.c.x {
		tmp := t.b
		t.b = t.c
		t.c = tmp
	}

	if t.a.x > t.b.x {
		tmp := t.a
		t.a = t.b
		t.b = tmp
	}

	if t.a.x == t.b.x && t.a.y > t.b.y {
		tmp := t.a
		t.a = t.b
		t.b = tmp
	}

	if t.b.x == t.c.x && t.b.y > t.c.y {
		tmp := t.b
		t.b = t.c
		t.c = tmp
	}

	if t.a.x == t.b.x && t.a.y > t.b.y {
		tmp := t.a
		t.a = t.b
		t.b = tmp
	}

}


func (t triangle) Hash() string {
	return fmt.Sprint(t.a.x,t.a.y,", ",t.b.x,t.b.y,", ",t.c.x,t.c.y)
}


func (t triangle) HasRightAngle() bool {

	if t.a.Equals(t.b) || t.b.Equals(t.c) || t.a.Equals(t.c) {
		return false
	}

	if t.a.x == t.b.x && t.b.x == t.c.x {
		return false
	}

	if t.a.y == t.b.y && t.b.y == t.c.y {
		return false
	}

	
	v1 := point{t.b.x-t.a.x,t.b.y-t.a.y}
	v2 := point{t.c.x-t.b.x,t.c.y-t.b.y}
	v3 := point{t.a.x-t.c.x,t.a.y-t.c.y}

	dp1 := v1.x*v2.x + v1.y*v2.y
	dp2 := v2.x*v3.x + v2.y*v3.y
	dp3 := v3.x*v1.x + v3.y*v1.y

	return dp1 == 0 || dp2 == 0 || dp3 == 0
}


func main() {

	rightTriangles := make(map[string]bool)

	a := point{0,0}

	min := 0
	max := 50

	for bx := min; bx <= max; bx += 1 {
		for by := min; by <= max; by += 1 {
			for cx := min; cx <= max; cx += 1 {
				for cy := min; cy <= max; cy += 1 {

					t := triangle{a,point{bx,by},point{cx,cy}}

					if t.HasRightAngle() == true {

						tUnsorted := t

						t.Sort()
						hash := t.Hash()

						if _, ok := rightTriangles[hash]; ok == false {

							rightTriangles[hash] = true

							fmt.Println(tUnsorted.Hash(), "/", len(rightTriangles))

						}

					}

				}
			}
		}
	}

}

