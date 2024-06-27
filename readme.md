# Nachos Console
the another console on C++

# Requirements
### OS:
- Windows 10 build 17063 or later (you can try to run on lower versions, but you will encounter problems)
- Linux

# HOW 2 COMPILE
### FOR WINDOWS (you need mingw installed)
##### x64: ```x86_64-w64-mingw32-g++ -static -lstdc++fs -std=c++17 main.cpp repo.cpp account.cpp pkg-del.cpp other_comms.cpp sha256.c -o main-win.exe```
##### x32: ```i686-w64-mingw32-g++ -static -lstdc++fs -std=c++17 main.cpp repo.cpp account.cpp pkg-del.cpp other_comms.cpp sha256.c -o main-win.exe```

### FOR LINUX
##### ```g++ -static -lstdc++fs -std=c++17 main.cpp repo.cpp account.cpp pkg-del.cpp other_comms.cpp sha256.c -o main```

#### or [download latest from releases](https://github.com/nachosteam/nachos-console/releases)
