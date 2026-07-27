package tools

import (
	"archive/tar"
	"compress/gzip"
	"errors"
	"io"
	"log"
	"os"
)

func ExtractTarGz(gzipStream io.Reader, path string) error {
	//original: https://stackoverflow.com/questions/57639648/how-to-decompress-tar-gz-file-in-go
	uncompressedStream, err := gzip.NewReader(gzipStream)
	if err != nil {
		log.Fatal("ExtractTarGz: NewReader failed")
	}

	tarReader := tar.NewReader(uncompressedStream)

	for true {
		header, err := tarReader.Next()

		if err == io.EOF {
			break
		}

		if err != nil {
			return err
		}

		switch header.Typeflag {
		case tar.TypeDir:
			if err := os.Mkdir(path+header.Name, 0755); err != nil {
				return err
			}
		case tar.TypeReg:
			outFile, err := os.Create(path + header.Name)
			if err != nil {
				return err
			}
			if _, err := io.Copy(outFile, tarReader); err != nil {
				return err
			}
			outFile.Close()

		default:
			return errors.New("Unknown type")
		}

	}

	return nil
}
