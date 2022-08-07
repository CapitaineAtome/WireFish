cmake_minimum_required(VERSION 3.20)

SET(PORJECT_NAME WireFish)

project(${PROJECT_NAME} WireFish)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)

add_compile_options(-Wall -Wextra -Wpedantic -Wshadow -Wnon-virtual-dtor
        -Wold-style-cast -Wunused -Woverloaded-virtual -Wsign-conversion
        -Wnull-dereference -Double-promotion -Wformat -Wno-format
        -Wno-unused-function -Wno-maybe-uninitialized)

add_executable(${PROJECT_NAME}
        sources/main.cpp
        sources/net/interface.cpp
        sources/net/device.cpp
        sources/packet/packet.cpp)