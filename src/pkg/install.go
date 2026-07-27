package pkg

import (
	"fmt"
	"os"
	"encoding/json"

	"nc/src/cli"
	"nc/src/net"
	"nc/src/user"
	"nc/src/sys"
)

func Install(pkgs []string) {
	fmt.Printf("[WIP] on install: %v\n", pkgs)

	// check if list is empty
	if (len(pkgs) <= 0) {
		fmt.Println("List is empty. Nothing to install.")
		return
	}

	// check if packages list exists
	pkgsCfg, errPkgsCfg := os.ReadFile(cli.Folder + "/packages.json")
	if errPkgsCfg != nil {
		fmt.Println("Failed to open 'packages.json'. Make sure you update it with \"pkg update\"")
		return;
	}

	pkgsList := make(map[string]interface{})
	errJson := json.Unmarshal(pkgsCfg, &pkgsList)
	if errJson != nil {
		fmt.Println("Failed to get JSON data from 'packages.json'.")
		return
	}

	for i := 0; i < len(pkgs); i++ {
		pkgDataRaw := pkgsList[pkgs[i]]
		if (pkgDataRaw == nil) {
			fmt.Println("Package doesn't exists. Aborting.")
			return
		}
		pkgData := pkgDataRaw.(map[string]interface{})

		pkgFolder := cli.Folder + "/" + pkgs[i];
		pkgFile := pkgs[i] + "-" + pkgData["version"].(string)
		if (pkgData["arch"].([]interface{})[0].(string) == "any") {
			pkgFile = pkgFile + "-any.tar.gz";
		} else {
			pkgFile = pkgFile + "-" + sys.Arch() + ".tar.gz";
		}


		os.Mkdir(pkgFolder, 0755)
		net.Download(user.Repo + "/" + sys.Os() + "/" + pkgFile, pkgFolder + "/" + pkgFile)

		fmt.Println("Package installed.")
	}
}
