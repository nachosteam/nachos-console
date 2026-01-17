package cli

import (
	"os"

	"nc/src/account"
)

const (
	folder string = "nc-bin"
	file   string = folder + "/cfg.json"
)

func Init() {
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
