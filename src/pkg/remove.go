package pkg

import (
	"bufio"
	"fmt"
	"nc/src/cli"
	"nc/src/sys"
	"os"
	"strings"
)

func Remove(pkgs []string) {
	fmt.Printf("Confirm removing packages(%d): %s\n[Y/n]: ", len(pkgs), strings.Join(pkgs, ", "))

	confirm, _ := bufio.NewReader(os.Stdin).ReadString('\n')
	confirm = strings.TrimSpace(confirm)
	confirmLower := strings.ToLower(confirm)

	if confirmLower != "y" && confirmLower != "yes" && confirmLower != "" {
		fmt.Println("Aborted by user.")
		return
	}

	removedInt := 0

	for i := 0; i < len(pkgs); i++ {
		if !sys.Exists(cli.Folder + "/" + pkgs[i]) {
			fmt.Println("Package " + pkgs[i] + " doesn't exists. Skipping.")
			continue
		}

		errRm := os.RemoveAll(cli.Folder + "/" + pkgs[i])
		if errRm != nil {
			fmt.Println(errRm)
			return
		}
		fmt.Println("Package " + pkgs[i] + " removed.")
		removedInt++
	}

	fmt.Printf("%d packages removed.\n", removedInt)
}
