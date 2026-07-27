package pkg

import (
	"fmt"

	"nc/src/cli"
	"nc/src/user"
	"nc/src/net"
	"nc/src/sys"
)

func Update() {
	err := net.Download(user.Repo + "/" + sys.Os() + "/packages.json", cli.Folder + "/packages.json")
	if err != nil {
		fmt.Println("Error downloading: " + err.Error())
		return
	}

	fmt.Println("Packages list updated.")
}