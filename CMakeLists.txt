cmake_minimum_required(VERSION 3.0)

project(stb-crop)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-Wall -Wno-psabi)

add_executable(stb-crop src/main.cpp)