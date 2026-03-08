package pkg

import "fmt"

func Install(pkgs []string) {
	fmt.Printf("on install: %v\n", pkgs)
	for i := 0; i < len(pkgs); i++ {
		fmt.Printf("pkg: %s\n", pkgs[i])
	}
}
