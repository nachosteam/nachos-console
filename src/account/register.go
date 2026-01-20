package account

import (
	"bufio"
	"crypto/sha256"
	"encoding/hex"
	"encoding/json"
	"fmt"
	"os"
	"strings"

	"nc/src/user"
)

func Register(file string) {
	fmt.Printf("There's no any accounts for program\nCreating the new one:\n")
	m := make(map[string]interface{})

	var name string

	fmt.Printf("| Username: ")
	fmt.Scanln(&name)
	m["name"] = name

	fmt.Printf("| Password: ")
	pass, _ := bufio.NewReader(os.Stdin).ReadString('\n')
	pass = strings.TrimSpace(pass)
	passHash := sha256.Sum256([]byte(pass))
	m["pass"] = hex.EncodeToString(passHash[:])

	m["pc"] = "pc"

	cfgJson, err := json.Marshal(m)
	if err != nil {
		panic(err)
	}
	os.WriteFile(file, []byte(cfgJson), 0644)

	user.Name = name
	user.Pc = "pc"
}
