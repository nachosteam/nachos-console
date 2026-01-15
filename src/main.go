package main

import "fmt"

const (
	NAME string = "Nachos Console"
	VER  string = "1.0.0"
)

func main() {
	for {
		fmt.Printf("%s %s\n", NAME, VER)
	}
}
