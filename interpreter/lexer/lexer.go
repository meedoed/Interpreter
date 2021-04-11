package main

import "fmt"

func main() {

	var a, b, n int

	fmt.Scan(&a, &b)
	for a > 0 {
		if a%10 == b {
			a /= 10
		} else {
			n = (n + a%10) * 10
			a /= 10
		}
	}
	n /= 10
	for n > 0 {
		a = (a + n%10) * 10
		n /= 10
	}

	fmt.Print(a / 10)

}
