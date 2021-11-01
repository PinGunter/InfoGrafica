cmake_minimum_required(VERSION 3.20)
project(Practica_IG)

set(CMAKE_CXX_STANDARD 14)
include_directories(include)
add_executable(Practica_IG
        include/aux.h
        include/cubo.h
        include/ejes.h
        include/escena.h
        include/malla.h
        include/objply.h
        include/objrevolucion.h
        include/ply_reader.h
        include/tetraedro.h
        include/tuplasg.h
        src/cubo.cc
        src/ejes.cc
        src/escena.cc
        src/malla.cc
        src/objply.cc
        src/objrevolucion.cc
        src/ply_reader.cc
        src/practicas.cc
        src/tetraedro.cc src/cilindro.cc include/cilindro.h src/esfera.cc include/esfera.h src/cono.cc include/cono.h)

target_link_libraries(Practica_IG  -lm -lGL -lglut -lGLU -lGLEW)
