package sys

import "runtime"

func Arch() string {
	return runtime.GOARCH
}