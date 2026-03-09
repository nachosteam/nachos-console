package pkg

import (
	"fmt"
	//"encoding/json"

	"nc/src/cli"
	"nc/src/user"
)

func Install(pkgs []string) {
	fmt.Printf("on install: %v\n", pkgs)
	for i := 0; i < len(pkgs); i++ {
		fmt.Printf("pkg: %s\n", pkgs[i])
	}
	fmt.Println(cli.Folder)
	fmt.Println(cli.File)
	
	fmt.Println(user.Repo)
}
