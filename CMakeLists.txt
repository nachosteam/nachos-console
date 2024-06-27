cmake_minimum_required(VERSION 3.5)
project(nachos-console)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O2 -Wextra -static -lstdc++fs -std=c++17")

set(SOURCE_FILES src/main.cpp
                 src/repo.cpp
                 src/account.cpp
                 src/pkg-del.cpp
                 src/other_comms.cpp)

add_executable(nachos-console ${SOURCE_FILES})
