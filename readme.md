# Nachos Console
the another console on C++

# Requirements
### Supported OS:
- Windows 10 build 17063 or later (you can try to run on lower versions, but you will encounter problems)
- GNU/Linux

# Compile 4 urself
### WINDOWS (you need mingw/MSYS installed)
##### x64: ```x86_64-w64-mingw32-g++ -static -lstdc++fs -std=c++17 main.cpp repo.cpp account.cpp pkg-del.cpp other_comms.cpp sha256.c -o main-win.exe```
##### x32: ```i686-w64-mingw32-g++ -static -lstdc++fs -std=c++17 main.cpp repo.cpp account.cpp pkg-del.cpp other_comms.cpp sha256.c -o main-win.exe```

### GNU/LINUX
```
git clone https://github.com/nachosteam/nachos-console
cd nachos-console
cmake .
make
```

#### or [just download latest from releases :D](https://github.com/nachosteam/nachos-console/releases)
