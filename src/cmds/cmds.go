package cmds

import "runtime"

var (
	CLEAR string
	DIR   string
)

func Init() {
	switch runtime.GOOS {
	// case "windows":
	// 	CLEAR = "cls"
	// 	DIR = "dir"
	// i hate ts, microsoft kys
	default:
		CLEAR = "clear"
		DIR = "ls"
	}
}
