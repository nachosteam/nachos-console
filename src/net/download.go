package net

import (
	"errors"
    "io"
    "net/http"
    "os"
)

func Download(url string, path string) error {
    resp, err := http.Get(url)
    if err != nil {
        return err
    }
    defer resp.Body.Close()

    if resp.StatusCode != http.StatusOK {
        return errors.New(resp.Status)
    }

    out, err := os.Create(path)
    if err != nil {
        return err
    }
    defer out.Close()

    _, err = io.Copy(out, resp.Body)
    if err != nil {
        return err
    }

    return nil
}