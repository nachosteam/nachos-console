package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"

	"github.com/fatih/color"
)

const (
	NAME string = "Nachos Console"
	VER  string = "1.0.0"
)

func main() {
	for {
		var comm string
		fullComm, _ := bufio.NewReader(os.Stdin).ReadString('\n')
		fullComm = strings.TrimSpace(fullComm)

		arr := strings.Split(fullComm, " ") // ета короче слова
		comm = arr[0]                       // а ета короче комманда
		params := arr[1:]                   // а ета короче параметры её

		fmt.Printf("\n---------\nfull: %s\nfirst word: %s\nparams: %v\n---------\n", fullComm, comm, params)

		// for _, j := range params[1:4] {
		// 	fmt.Printf("PACKET %s\n", j)
		// }

		switch comm {
		case "help":
			fmt.Printf("")
		case "about":
			fmt.Printf(`..................
..#.....#..######.	 %s
..##....#....#....	 %s
..#.#...#....#....	 By %s 2001
..#..#..#....#....	 https://github.com/nachosteam/nachos-console
..#...#.#....#....
..#....##....#....	 %s
..#.....#....#....
..................
`, NAME, VER, color.YellowString("NachosTeam"), color.CyanString("Under MIT License"))

		default:
			fmt.Printf("ээ тi чо ахуел '%s'\n", fullComm)
		}
	}
}
