package cmds

import (
	"fmt"
	"os"

	"github.com/fatih/color"
)

func ShowDir(dir string) {
	entries, err := os.ReadDir(dir)
	if err != nil {
		panic(err)
	}

	for _, entry := range entries {
		if entry.IsDir() {
			fmt.Printf("%s\t", color.CyanString(entry.Name()))
		} else {
			fmt.Printf("%s\t", entry.Name())
		}
	}

	fmt.Printf("\n")
}
