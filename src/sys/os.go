package sys

import "runtime"

func Os() string {
	return runtime.GOOS
}