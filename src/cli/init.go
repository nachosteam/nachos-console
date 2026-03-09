package cli

import (
	"os"

	"nc/src/account"
)

const (
	Folder string = "./nc-bin"
	File   string = Folder + "/cfg.json"

	test int = 0
)

func Init() {
	if test == 1 {
		errRm := os.RemoveAll(Folder)
		if errRm != nil {
			panic(errRm)
		}
	}

	cfg, err := os.Open(File)
	if err != nil {
		if os.IsNotExist(err) {
			os.Mkdir(Folder, 0755)
			os.Create(File)
			// err = os.WriteFile(cfg)
			account.Register(File) //starts the registration process

		} else {
			panic(err)
		}
	} else {
		account.Login(File)
	}
	cfg.Close()
}
