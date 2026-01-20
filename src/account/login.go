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

func Login(file string) {
	cfg, errCfg := os.ReadFile(file)
	if errCfg != nil {
		panic(errCfg)
	}

	m := make(map[string]interface{})
	errJson := json.Unmarshal(cfg, &m)
	if errJson != nil {
		panic(errJson)
	}

	reader := bufio.NewReader(os.Stdin)

	fmt.Printf("| Username: ")
	username, _ := reader.ReadString('\n')
	username = strings.TrimSpace(username)
	if username != m["name"].(string) {
		panic("User does not exist\n\n")
	}

	fmt.Printf("| Password: ")
	pass, _ := reader.ReadString('\n')
	pass = strings.TrimSpace(pass)
	passHashTempBytes := sha256.Sum256([]byte(pass))
	passHashTemp := hex.EncodeToString(passHashTempBytes[:])
	if passHashTemp != m["pass"].(string) {
		panic("Password is incorrect\n\n")
	}

	user.Name = username
	user.Pc = m["pc"].(string)
}
