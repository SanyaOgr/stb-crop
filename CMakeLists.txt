cmake_minimum_required(VERSION 3.0)

project(stb-cut)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(stb-cut src/main.cpp src/stb_image.h src/stb_image_write.h)

target_compile_options(stb-cut PRIVATE -Wall -Wextra -Werror -pedantic)

install(TARGETS stb-cut RUNTIME DESTINATION bin)
install(FILES ${CMAKE_SOURCE_DIR}/scripts/cut.sh DESTINATION bin)