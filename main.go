package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"

	"nc/src/cli"
	"nc/src/pkg"
	"nc/src/user"

	"github.com/fatih/color"
)

const (
	NAME string = "Nachos Console"
	VER  string = "1.0.0"
)

func main() {
	cli.Init()

	for {
		fmt.Printf("%s@%s$ ", user.Name, user.Pc)

		var comm string
		fullComm, _ := bufio.NewReader(os.Stdin).ReadString('\n')
		fullComm = strings.TrimSpace(fullComm)

		arr := strings.Split(fullComm, " ") // ета короче слова
		comm = arr[0]                       // а ета короче комманда
		params := arr[1:]                   // а ета короче параметры её

		switch comm {
		case "":
			continue
		case "help":
			fmt.Printf("help   display command list\n" +
				"about  display program version\n" +
				"echo   display entered text\n" +
				"pkg [parameter] [package]   manage program's packages\n" +
				"exit   closes the program\n")
		case "echo":
			fmt.Println(strings.Join(params, " "))
		case "about":
			fmt.Printf("..................\n"+
				"..#.....#..######.  %s\n"+
				"..##....#....#....  %s\n"+
				"..#.#...#....#....  By %s 2024 - 2026\n"+
				"..#..#..#....#....  https://github.com/nachosteam/nachos-console\n"+
				"..#...#.#....#....\n"+
				"..#....##....#....  %s\n"+
				"..#.....#....#....  %s\n"+
				"..................\n",
				NAME, VER, color.YellowString("NachosTeam"), "Golang Rewrite Preview", color.CyanString("Under MIT License"))
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
				fmt.Printf("Package manager for %s\n"+
					"Enter \"pkg help\" to see available commands\n", NAME)
			}
		case "exit":
			return

		default:
			fmt.Printf("Unknown command: %q\n", comm)
		}
	}
}
