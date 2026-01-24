package cli

import (
	"os"

	"nc/src/account"
	"nc/src/cmds"
)

const (
	folder string = "./nc-bin"
	file   string = folder + "/cfg.json"

	test int = 0
)

func Init() {
	cmds.Init()

	if test == 1 {
		errRm := os.RemoveAll(folder)
		if errRm != nil {
			panic(errRm)
		}
	}

	cfg, err := os.Open(file)
	if err != nil {
		if os.IsNotExist(err) {
			os.Mkdir(folder, 0644)
			os.Create(file)
			// err = os.WriteFile(cfg)
			account.Register(file) //starts the registration process

		} else {
			panic(err)
		}
	} else {
		account.Login(file)
	}
	cfg.Close()
}
