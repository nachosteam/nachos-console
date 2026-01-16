package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"

	"nc/src/pkg"

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
		case "":
			continue
		case "help":
			fmt.Printf("help   display command list\n" +
				"about  display programm version\n" +
				"echo   display entered text" +
				"pkg [parameter] [package]   manage programm's packages\n" +
				"exit   closes the programm\n")
		case "echo":
			fmt.Println(strings.Join(params, " "))
		case "about":
			fmt.Printf("..................\n"+
				"..#.....#..######.	 %s\n"+
				"..##....#....#....	 %s\n"+
				"..#.#...#....#....	 By %s 2024 - 2026\n"+
				"..#..#..#....#....	 https://github.com/nachosteam/nachos-console\n"+
				"..#...#.#....#....\n"+
				"..#....##....#....	 %s\n"+
				"..#.....#....#....\n"+
				"..................\n",
				NAME, VER, color.YellowString("NachosTeam"), color.CyanString("Under MIT License"))
		case "pkg":
			if len(params) >= 1 {
				switch params[0] {
				case "help":
					fmt.Printf("pkg install [package(s)]   install package(s)\n" +
						"pkg remove [package(s)]   remove package(s)\n")
				case "install":
					pkg.Install(params[1:])
				case "remove":
					pkg.Remove(params[1:])
				default:
					fmt.Printf("pkg: Unknown parameter: %q\nEnter \"pkg help\" to see available commands\n", params[0])
				}
			} else {
				fmt.Println("pkg: none")
			}
		case "exit":
			return

		default:
			fmt.Printf("Unknown command: %q\n", comm)
		}
	}
}
