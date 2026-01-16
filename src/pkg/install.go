package pkg

import "fmt"

func Install(pkgs []string) {
	fmt.Printf("on install: %v\n", pkgs)
}
