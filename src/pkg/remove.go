package pkg

import (
	"fmt"
	"nc/src/cli"
	"os"
)

func Remove(pkgs []string) {
	fmt.Printf("[WIP] on remove: %v\n", pkgs)

	return

	for i := 0; i < len(pkgs); i++ {
		errRm := os.RemoveAll(cli.Folder + "/" + pkgs[i])
		if errRm != nil {
			panic(errRm)
		}
	}
}
