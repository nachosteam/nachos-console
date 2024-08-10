# Nachos Console
the another console on C++

# Requirements
### Supported OS:
- Windows 7+
- GNU/Linux

# How2Compile
### WINDOWS (you need mingw/MSYS installed)
##### x64: ```x86_64-w64-mingw32-g++ -static -lstdc++fs -std=c++17 main.cpp repo.cpp account.cpp pkg-del.cpp other_comms.cpp sha256.c -o main-win.exe```
##### x32: ```i686-w64-mingw32-g++ -static -lstdc++fs -std=c++17 main.cpp repo.cpp account.cpp pkg-del.cpp other_comms.cpp sha256.c -o main-win.exe```
#### or [just download latest from releases](https://github.com/nachosteam/nachos-console/releases)

### GNU/LINUX
```
git clone https://github.com/nachosteam/nachos-console
cd nachos-console
cmake .
make
```