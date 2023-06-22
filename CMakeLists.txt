cmake_minimum_required(VERSION 3.0)

project(stb-crop)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(stb-crop src/main.cpp src/stb_image.h src/stb_image_write.h)

target_compile_options(stb-crop PRIVATE -Wall -Wextra -pedantic -Os -ffunction-sections -fdata-sections)
target_link_options(stb-crop PRIVATE -Wl,--gc-sections -no-pie)
