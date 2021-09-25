cmake_minimum_required(VERSION 3.19)
project(pruebasOpenGL C)

set(CMAKE_C_STANDARD 99)

add_executable(pruebasOpenGL main.c)

target_link_libraries(pruebasOpenGL -lm -lGL -lglut -lGLU)