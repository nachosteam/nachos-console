package cli

import (
	"os"

	"nc/src/account"
)

const (
	Folder string = "./nc-bin"
	File   string = Folder + "/cfg.json"
)

func Init() {
	cfg, err := os.Open(File)
	if err != nil {
		if os.IsNotExist(err) {
			os.Mkdir(Folder, 0755)
			os.Create(File)
			account.Register(File) //starts the registration process

		} else {
			panic(err)
		}
	} else {
		account.Login(File)
	}
	cfg.Close()
}
