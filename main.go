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

		// fmt.Printf("\n---------\nfull: %s\nfirst word: %s\nparams: %v\n---------\n", fullComm, comm, params)

		switch comm {
		case "help":
			fmt.Printf("help   display command list\n" +
				"about  display programm version\n" +
				"exit   closes the programm\n" +
				"pkg [parameter] [package]   manage programm's packages\n")

		case "about":
			fmt.Printf(`..................
..#.....#..######.	 %s
..##....#....#....	 %s
..#.#...#....#....	 By %s 2026
..#..#..#....#....	 https://github.com/nachosteam/nachos-console
..#...#.#....#....
..#....##....#....	 %s
..#.....#....#....
..................
`, NAME, VER, color.YellowString("NachosTeam"), color.CyanString("Under MIT License"))
		case "":
			continue
		case "exit":
			return
		case "pkg":
			if len(params) >= 1 {
				switch params[0] {
				case "help":
					fmt.Printf("pkg install [package]\tinstall package\n")
				case "install":
					fmt.Printf("pkg: install\n")
				default:
					fmt.Printf("pkg: Unknown parameter: \"%s\"\nEnter \"pkg help\" to see available commands\n", params[0])
				}
			} else {
				fmt.Println("pkg: none")
			}

		default:
			fmt.Printf("Unknown command: \"%s\"\n", comm)
		}
	}
}
