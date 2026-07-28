package pkg

import (
	"encoding/json"
	"fmt"
	"os"

	"nc/src/cli"
	"nc/src/net"
	"nc/src/sys"
	"nc/src/tools"
	"nc/src/user"
)

func Install(pkgs []string) {
	// check if list is empty
	if len(pkgs) <= 0 {
		fmt.Println("List is empty. Nothing to install.")
		return
	}

	// check if packages list exists
	pkgsCfg, errPkgsCfg := os.ReadFile(cli.Folder + "/packages.json")
	if errPkgsCfg != nil {
		fmt.Println("Failed to open 'packages.json'. Make sure you update it with \"pkg update\"")
		return
	}

	pkgsList := make(map[string]interface{})
	errJson := json.Unmarshal(pkgsCfg, &pkgsList)
	if errJson != nil {
		fmt.Println("Failed to get JSON data from 'packages.json'.")
		return
	}

	for i := 0; i < len(pkgs); i++ {
		pkgDataRaw := pkgsList[pkgs[i]]
		if pkgDataRaw == nil {
			fmt.Println("Package \"" + pkgs[i] + "\" doesn't exists. Aborting.")
			return
		}
		pkgData := pkgDataRaw.(map[string]interface{})

		pkgFolder := cli.Folder + "/" + pkgs[i]
		pkgFile := pkgs[i] + "-" + pkgData["version"].(string)
		if pkgData["arch"].([]interface{})[0].(string) == "any" {
			pkgFile = pkgFile + "-any.tar.gz"
		} else {
			pkgFile = pkgFile + "-" + sys.Arch() + ".tar.gz"
		}

		os.Mkdir(pkgFolder, 0755)
		net.Download(user.Repo+"/"+sys.Os()+"/"+pkgFile, pkgFolder+"/"+pkgFile)

		pkgArchive, err := os.Open(pkgFolder + "/" + pkgFile)
		if err != nil {
			fmt.Println(err)
			return
		}

		extractErr := tools.ExtractTarGz(pkgArchive, pkgFolder+"/")
		pkgArchive.Close()
		if extractErr != nil {
			fmt.Println("Failed to decompress archive: " + extractErr.Error())
			archiveErr := os.Remove(pkgFolder + "/" + pkgFile)
			if archiveErr != nil {
				fmt.Println(archiveErr)
			}
			return
		}
		archiveErr := os.Remove(pkgFolder + "/" + pkgFile)
		if archiveErr != nil {
			fmt.Println("Failed to install package: " + archiveErr.Error())
			return
		}

		if sys.Os() != "windows" {
			pkgInfo, errPkg := os.ReadFile(pkgFolder + "/package.json")
			if errPkg != nil {
				fmt.Println(errPkg)
				return
			}

			m := make(map[string]interface{})
			errJson := json.Unmarshal(pkgInfo, &m)
			if errJson != nil {
				fmt.Println(errJson)
				return
			}

			os.Chmod(pkgFolder+"/"+m["executable"].(string), 0755)
		}

		fmt.Println("Package installed.")
	}
}
